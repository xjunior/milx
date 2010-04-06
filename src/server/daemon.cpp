#include "../logger.hpp"
#include "../web_call.hpp"
#include "daemon.hpp"

Milx::Server::Daemon::Daemon(Milx::Application &app, int port) :
	_app(app),
	_port(port),
	_running(false)
{
}

int Milx::Server::Daemon::_queue_response(struct MHD_Connection *conn, Milx::WebCall &call)
{
	struct MHD_Response *response;
	response = MHD_create_response_from_data(call.response_content().size(),
				(void *)call.response_content().c_str(), MHD_NO, MHD_NO);
	// MHD_add_response_header(response, MHD_HTTP_HEADER_CONTENT_TYPE, (call.mime_type() + "; charset=" + call.encoding()).c_str());
	int ret = MHD_queue_response(conn, 200, response);
	MHD_destroy_response(response);

	return ret;
}

int Milx::Server::Daemon::_copy_values(void *cls, enum MHD_ValueKind kind, const char *key, const char *value)
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

int Milx::Server::Daemon::_connection_dispatcher(void *cls, struct MHD_Connection *conn,
							const char *path, const char *method,
							const char *version, const char *upload_data,
							size_t *upload_data_size, void **con_cls)
{
	Milx::Application *app = (Milx::Application*)cls;

	Milx::CallMethod mtd;
	if (strcmp(method, "GET") == 0) mtd = METHOD_GET;
	else if (strcmp(method, "POST") == 0) mtd = METHOD_POST;
	else if (strcmp(method, "PUT") == 0) mtd = METHOD_PUT;
	else if (strcmp(method, "DELETE") == 0) mtd = METHOD_DELETE;

	Milx::WebCall call(mtd, path);

	MHD_get_connection_values(conn, MHD_HEADER_KIND, &Milx::Server::Daemon::_copy_values, &call);
	MHD_get_connection_values(conn, MHD_GET_ARGUMENT_KIND, &Milx::Server::Daemon::_copy_values, &call);
	MHD_get_connection_values(conn, MHD_POSTDATA_KIND, &Milx::Server::Daemon::_copy_values, &call);

	app->dispatch(call);

	return _queue_response(conn, call);
}

void Milx::Server::Daemon::start()
{
	_mhdaemon = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION, _port, NULL, NULL,
			&Milx::Server::Daemon::_connection_dispatcher,
			&_app, MHD_OPTION_END);
	_running = true;
	_app.logger()->info("Server started listening on ") << _port << std::endl;
}

void Milx::Server::Daemon::stop()
{
	MHD_stop_daemon(_mhdaemon);
	_running = false;
	_app.logger()->info("Server stopped") << std::endl;
}

