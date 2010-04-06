#include <cstring>
#include <iostream>
#include <csignal>
#include "../server/daemon.hpp"
#include "../application.hpp"
#include "../project_loader.hpp"
#include "server_command.hpp"

Milx::Server::Daemon *Milx::CLI::ServerCommand::_daemon;

Milx::CLI::ReturnValue Milx::CLI::ServerCommand::main(int argc, char* argv[])
{
	if (argc >= 2) {
		if (argc == 3) _path = argv[2];
		else _path = fs::current_path();

		if (strcmp(argv[1], "start") == 0) {
			return start_server(8888);
		} else if (strcmp(argv[1], "stop") == 0) {
			return stop_server();
		} else if (strcmp(argv[1], "restart") == 0) {
			if (stop_server() == CLI_SUCCESS) {
				return start_server(8888);
			} else return CLI_FAIL;
		}
	}
	return CLI_SHOW_HELP;
}

void Milx::CLI::ServerCommand::show_help()
{
}

const char* Milx::CLI::ServerCommand::description()
{
	return "Manage milx built-in server";
}

Milx::CLI::ReturnValue Milx::CLI::ServerCommand::start_server(int port)
{
	std::cout << "Starting!" << std::endl;
	// TODO test if the pid file already exist and so not start
	// a --force flag would be nice to force a restart
	// in this case, restart action would be deprecated

	if (!fork()) {
		setsid(); // detach

		Milx::Application app;
		Milx::ProjectLoader::load(app, _path);
		_daemon = new Milx::Server::Daemon(app, port);
		_daemon->start();

		std::ofstream log((_path / "milx-server.log").string().c_str(), std::ios_base::app);
		app.logger(new Milx::Logger(log));

		struct sigaction action;
		action.sa_handler = &Milx::CLI::ServerCommand::_stop_server;
		sigaction(SIGALRM, &action, NULL);

		std::ofstream fstream((_path / "milx-server.pid").string().c_str());
		fstream << getpid();
		fstream.close();

		while(_daemon->running());

		log.close();
	}

	return CLI_SUCCESS;
}

Milx::CLI::ReturnValue Milx::CLI::ServerCommand::stop_server()
{
	std::cout << "Stoping!" << std::endl;
	std::ifstream fstream((_path / "milx-server.pid").string().c_str());
	std::string pid;
	fstream >> pid;
	fstream.close();
	kill(atoi(pid.c_str()), SIGALRM);
//	remove_pid_file();

	return CLI_SUCCESS;
}

void Milx::CLI::ServerCommand::_stop_server(int)
{
	_daemon->stop();
}

