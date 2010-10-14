/*
 * Copyright 2010 Carlos Junior
 *
 * This file is part of Milx.
 *
 * Milx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Milx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Milx.  If not, see <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

#include <milx/server/daemon.h>

#include <fcntl.h>

#include <iterator>
#include <fstream>
#include <string>

#include <milx/milx.h>
#include <milx/logger.h>
#include <milx/http.h>

#define MILX_SERVER_NAME "Milx Server v"

struct ConnectionInfo {
  milx::http::Call *call;
  int file;  // File descriptor
  struct MHD_PostProcessor *pp;
};

int _queue_response(struct MHD_Connection *conn, milx::http::Call* call) {
  struct MHD_Response *response = NULL;

  if (call->file_content() != NULL) {
    #if MHD_VERSION >= 0x00090000
      int file = open(call->file_content()->str().c_str(), O_RDONLY);
      response = MHD_create_response_from_fd(
        call->file_content()->stat().size(),
        file);
    #else
      std::ifstream infile(call->file_content()->str().c_str(), std::ios::in);
      if (infile.is_open()) {
        call->content().str("");
        call->content().flush();
        call->content().clear();
        std::istreambuf_iterator<char> file_begin(infile.rdbuf());
        const std::istreambuf_iterator<char> file_end;
        while (!file_begin.equal(file_end)) call->content() << *file_begin++;
        infile.close();
      } else {
        // TODO(xjunior) become an error 500 or throw exception
      }
    #endif
  }

  if (!response) {
    std::string content = call->content().str();
    response = MHD_create_response_from_data(content.size(),
          const_cast<char*>(content.c_str()), MHD_NO, MHD_YES);
  }

  MHD_add_response_header(response, MHD_HTTP_HEADER_SERVER,
                          (MILX_SERVER_NAME + milx::version()).c_str());
  MHD_add_response_header(response, MHD_HTTP_HEADER_CONTENT_TYPE,
                          call->content_type().c_str());
  int ret = MHD_queue_response(conn, call->status(), response);
  MHD_destroy_response(response);

  return ret;
}

int _copy_values(void *cls, enum MHD_ValueKind kind,
  const char *key, const char *value) {
  switch (kind) {
    case MHD_HEADER_KIND:
      ((milx::http::Call*)cls)->header[key] = value;
      break;
    case MHD_GET_ARGUMENT_KIND:
    case MHD_POSTDATA_KIND:
      ((milx::http::Call*)cls)->params[key] = value;
      break;
  }

  return MHD_YES;
}

int _post_values(void *cls, enum MHD_ValueKind kind,
  const char *key, const char *filename, const char *content_type,
  const char *transfer_encoding, const char *data, uint64_t off, size_t size) {
}

bool _static_access(milx::server::Daemon* server, milx::http::Call& call) {
  if (server->public_dir_enabled()) {
    milx::Path tmp = server->public_dir() / call.path();
    if (tmp.exists())
      if (tmp.stat().is_file()) {
        call.content(tmp);
        return true;
      } else {
        if (tmp.stat().is_dir())
          for (register int i = 0; i < server->index.size(); i++) {
            milx::Path::List indexes =
                milx::Path::ls((tmp / server->index[i]).str());
            if (indexes.size()) {
              call.content(indexes.front());
              return true;
            }
          }
      }
  }

  return false;
}

void* _close_request(void *cls, struct MHD_Connection* con, void **con_cls,
  enum MHD_RequestTerminationCode toe) {
  struct ConnectionInfo * info = (struct ConnectionInfo *)*con_cls;
  milx::server::Daemon *server = (milx::server::Daemon*)cls;

  MHD_destroy_post_processor(info->pp);
  delete info->call;
}

int _connection_dispatcher(void *cls,
  struct MHD_Connection *conn,
  const char *path, const char *method,
  const char *version, const char *upload_data,
  size_t *upload_data_size, void **con_cls) {
  struct ConnectionInfo * info = (struct ConnectionInfo *)*con_cls;
  milx::server::Daemon *server = (milx::server::Daemon*)cls;

  if (info == NULL) {
    *con_cls = info = new ConnectionInfo;
    info->pp = MHD_create_post_processor(conn, 1024, &_post_values, cls);

    milx::http::Method mtd;
    if (strcmp(method, "GET") == 0) mtd = milx::http::GET;
    else if (strcmp(method, "POST") == 0) mtd = milx::http::POST;
    else if (strcmp(method, "PUT") == 0) mtd = milx::http::PUT;
    else if (strcmp(method, "DELETE") == 0) mtd = milx::http::DELETE;

    info->call = new milx::http::Call(mtd, path);

    return MHD_YES;
  }

  if (*upload_data_size) {
    MHD_post_process(info->pp, upload_data, *upload_data_size);
    *upload_data_size = 0;

    return MHD_YES;
  }  // else {

  if (!_static_access(server, *info->call)) {
    // nothing of this is used in static calls
    MHD_get_connection_values(conn, MHD_HEADER_KIND,
        &_copy_values, info->call);
    MHD_get_connection_values(conn, MHD_GET_ARGUMENT_KIND,
        &_copy_values, info->call);
    MHD_get_connection_values(conn, MHD_POSTDATA_KIND,
        &_copy_values, info->call);
    // TODO(xjunior) post processor
    server->application().dispatch(*info->call);
  }

  *con_cls = reinterpret_cast<void*>(info);

  return _queue_response(conn, info->call);
  // }
}

milx::server::Daemon::Daemon(milx::Application &app, int port)
  : _app(app), _port(port), _running(false),
  _public(milx::Path::cwd()), _use_public(true) {
  index.push_back("index.*");
}

bool milx::server::Daemon::start() {
  _mhdaemon = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION, _port, NULL, NULL,
    &_connection_dispatcher, this, MHD_OPTION_END);
  // TODO(xjunior) enable MHD_OPTION_EXTERNAL_LOGGER
  // TODO(xjunior) enable MHD_OPTION_URI_LOG_CALLBACK
  if (_running = (_mhdaemon != NULL)) {
    _app.logger().info() << "Server started listening on port" << _port;
    return true;
  } else {
    _app.logger().error() << "Server failed to start on port" << _port;
    return false;
  }
}

bool milx::server::Daemon::stop() {
  if (_running) {
    MHD_stop_daemon(_mhdaemon);
    _running = false;
    _app.logger().info() << "Server stopped";
    return true;
  }
  return false;
}

milx::server::Daemon::~Daemon() {
  stop();
  // if (_mhdaemon) delete _mhdaemon;
}

