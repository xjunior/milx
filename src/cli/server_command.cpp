#include <cstring>
#include <iostream>
#include <fstream>
#include <csignal>
#include "../server/daemon.hpp"
#include "../application.hpp"
#include "../project_loader.hpp"
#include "server_command.hpp"

Milx::Server::Daemon *Milx::CLI::ServerCommand::_daemon;

#define SERVER_LOG_FILE (_path / "milx-server.log")
#define SERVER_PID_FILE (_path / "milx-server.pid")

Milx::CLI::ReturnValue Milx::CLI::ServerCommand::main(int argc, char* argv[])
{
	if (argc >= 1) {
		if (argc == 2) _path = argv[1];
		else _path = Milx::Path::cwd();

		if (strcmp(argv[0], "start") == 0) {
			return start_server(8888);
		} else if (strcmp(argv[0], "stop") == 0) {
			return stop_server();
		} else if (strcmp(argv[0], "restart") == 0) {
			if (stop_server() == CLI_SUCCESS)
				return start_server(8888);
			else return CLI_FAIL;
		}
	}
	return CLI_SHOW_HELP;
}

const char* Milx::CLI::ServerCommand::help()
{
	return "server [start|stop|restart]";
}

const char* Milx::CLI::ServerCommand::description()
{
	return "Manage milx built-in server";
}

const char* Milx::CLI::ServerCommand::command()
{
	return "server";
}

Milx::CLI::ReturnValue Milx::CLI::ServerCommand::start_server(int port)
{
	if (SERVER_PID_FILE.exists()) {
		std::cout << "A server is already started!" << std::endl;
		return CLI_FAIL;
	} else {
		// TODO: create option for --wait
		if (fork()) return CLI_SUCCESS; // finish parent
		else setsid(); // detach

		Milx::Application app;

		std::ofstream log(SERVER_LOG_FILE.str().c_str(), std::ios_base::app);
		app.logger(new Milx::Logger(log));

		Milx::ProjectLoader::load(app, _path);
		Milx::Path::initialize_mime_magic(Milx::Path());
		Milx::Path::initialize_mime_map(Milx::Path("/etc/mime.types")); // TODO make it changeable somehow
		_daemon = new Milx::Server::Daemon(app, port);
		_daemon->public_dir(new Milx::Path(_path / "public"));
		_daemon->start();

		struct sigaction action;
		action.sa_handler = &Milx::CLI::ServerCommand::_stop_server;
		sigaction(SIGTERM, &action, NULL);

		std::ofstream pid(SERVER_PID_FILE.str().c_str());
		pid << getpid();
		pid.close();

		while(_daemon->running()); //  if !SIGALRM received

		log.close();
	}

	return CLI_SUCCESS;
}

Milx::CLI::ReturnValue Milx::CLI::ServerCommand::stop_server()
{
	if (SERVER_PID_FILE.exists()) {
		std::ifstream fstream(SERVER_PID_FILE.str().c_str());
		std::string pid;
		fstream >> pid;
		fstream.close();
		kill(atoi(pid.c_str()), SIGTERM);
		unlink(SERVER_PID_FILE.str().c_str());
	}

	return CLI_SUCCESS;
}

void Milx::CLI::ServerCommand::_stop_server(int)
{
	_daemon->stop();
}
