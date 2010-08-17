/*
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

#include <iterator>
#include <fstream>
#include <fcntl.h>

#include "../logger.hpp"
#include "../web_call.hpp"
#include "daemon.hpp"

Milx::Server::Daemon::Daemon(Milx::Application &app, int port) :
	_app(app),
	_port(port),
	_running(false)
{
	_public = new Milx::Path(Milx::Path::cwd());
	index.push_back("index.*");
}

int Milx::Server::Daemon::_queue_response(struct MHD_Connection *conn, Milx::WebCall &call)
{
	struct MHD_Response *response;

	if (call.file_content() != NULL) {
		#if MHD_VERSION >= 0x00090000 && 0
			// FIXME SEGFAULT when connection becomes idle
			int file;
			file = open(call.file_content()->str().c_str(), O_RDONLY);
			response = MHD_create_response_from_fd(call.file_content()->stat().size(), file);
		#else
			std::ifstream infile(call.file_content()->str().c_str(), std::ios::in);
			if (infile.is_open()) {
				call.content().str("");
				call.content().flush();
				call.content().clear();
				std::istreambuf_iterator<char> file_begin(infile.rdbuf());
				const std::istreambuf_iterator<char> file_end;
				while (!file_begin.equal(file_end)) call.content() << *file_begin++;
				infile.close();
			} else;
				// TODO become an error 500 or throw exception
		#endif
	}

	if (!response) {
		std::string content = call.content().str();
		response = MHD_create_response_from_data(content.size(),
					const_cast<char*>(content.c_str()), MHD_NO, MHD_YES);
	}

	MHD_add_response_header(response, MHD_HTTP_HEADER_SERVER, MILX_SERVER_NAME);
	MHD_add_response_header(response, MHD_HTTP_HEADER_CONTENT_TYPE, call.content_type().c_str());
	int ret = MHD_queue_response(conn, call.status(), response);
	MHD_destroy_response(response);

	return ret;
}

int Milx::Server::Daemon::_copy_values(void *cls, enum MHD_ValueKind kind,
	const char *key, const char *value)
{
	switch (kind) {
		case MHD_HEADER_KIND:
			// TODO
			break;
		case MHD_GET_ARGUMENT_KIND:
		case MHD_POSTDATA_KIND:
			((Milx::WebCall*)cls)->params[key] = value;
			break;
	}

	return MHD_YES;
}

int Milx::Server::Daemon::_post_values(void *cls, enum MHD_ValueKind kind,
	const char *key, const char *filename, const char *content_type,
	const char *transfer_encoding, const char *data, uint64_t off, size_t size)
{
}

int Milx::Server::Daemon::_connection_dispatcher(void *cls,
	struct MHD_Connection *conn,
	const char *path, const char *method,
	const char *version, const char *upload_data,
	size_t *upload_data_size, void **con_cls)
{
	if (*con_cls == NULL) {
		/*struct MHD_PostProcessor *pp = *con_cls;

		if (pp == NULL) {
			pp = MHD_create_post_processor(conn, 1024,
					&Milx::Server::Daemon::_post_values, &call);
			*con_cls = pp;
			return MHD_YES;
		}
		if (*upload_data_size) {
			MHD_post_process(pp, upload_data, *upload_data_size);
			*upload_data_size = 0;
			return MHD_YES;
		} else {
			MHD_destroy_post_processor(pp);
		}
		// finish here
		 */
		Milx::Server::Daemon *server = (Milx::Server::Daemon*)cls;

		Milx::CallMethod mtd;
		if (strcmp(method, "GET") == 0) mtd = METHOD_GET;
		else if (strcmp(method, "POST") == 0) mtd = METHOD_POST;
		else if (strcmp(method, "PUT") == 0) mtd = METHOD_PUT;
		else if (strcmp(method, "DELETE") == 0) mtd = METHOD_DELETE;

		Milx::WebCall call(mtd, path);
		bool dynamic = true;

		// XXX make it better, please
		if (server->public_dir() != NULL) {
			Milx::Path tmp = (*server->public_dir()) / path;
			if (tmp.exists())
				if (tmp.stat().is_file()) {
					call.content(tmp);
					dynamic = false;
				} else if (tmp.stat().is_dir())
					for (register int i = 0; i < server->index.size(); i++) {
						Milx::Path::List indexes = Milx::Path::ls((tmp / server->index[i]).str());
						if (indexes.size()) {
							call.content(indexes.front());
							dynamic = false;
						}
					}
		}

		if (dynamic) {
			MHD_get_connection_values(conn, MHD_HEADER_KIND,
					&Milx::Server::Daemon::_copy_values, &call);
			MHD_get_connection_values(conn, MHD_GET_ARGUMENT_KIND,
					&Milx::Server::Daemon::_copy_values, &call);
			MHD_get_connection_values(conn, MHD_POSTDATA_KIND,
					&Milx::Server::Daemon::_copy_values, &call);

			server->application().dispatch(call);
		}

		*con_cls = (void*) &call;

		return _queue_response(conn, call);
	} else {
		return MHD_YES;
	}
}

void Milx::Server::Daemon::start()
{
	_mhdaemon = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION, _port, NULL, NULL,
		&Milx::Server::Daemon::_connection_dispatcher, this, MHD_OPTION_END);
	// TODO enable MHD_OPTION_EXTERNAL_LOGGER
	// TODO enable MHD_OPTION_URI_LOG_CALLBACK
	// TODO enable MHD_OPTION_NOTIFY_COMPLETED
	if (_running = _mhdaemon != NULL)
		_app.logger()->info("Server started listening on ") << _port;
}

void Milx::Server::Daemon::stop()
{
	if (_running) {
		MHD_stop_daemon(_mhdaemon);
		_running = false;
		_app.logger()->info("Server stopped");
	}
}

Milx::Server::Daemon::~Daemon()
{
	stop();
}
