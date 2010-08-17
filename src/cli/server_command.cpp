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
	if (argc >= 2) {
		int opt;
		char *cmd = argv[1];
		while ((opt = getopt(argc, argv, "wp:d:")) != -1) {
			switch (opt) {
			case 'w': wait = true; break;
			case 'p': port = atoi(optarg); break;
			case 'd': _path = optarg; break;
			}
		}

		if (strcmp(cmd, "start") == 0) {
			return start_server();
		} else if (strcmp(cmd, "stop") == 0) {
			return stop_server();
		} else if (strcmp(cmd, "restart") == 0) {
			if (stop_server() == CLI_SUCCESS)
				return start_server();
			else return CLI_FAIL;
		}
	}
	return CLI_SHOW_HELP;
}

const char* Milx::CLI::ServerCommand::help()
{
	return "server [start|stop|restart] [options]\n" \
		"-d <path>\tproject root (default to current)\n"\
		"-w\t\tdon't go to background, wait until you press any key to finish\n"\
		"-p <port>\tport (default to 8888)";
}

const char* Milx::CLI::ServerCommand::description()
{
	return "Manage milx built-in server";
}

const char* Milx::CLI::ServerCommand::command()
{
	return "server";
}

Milx::CLI::ReturnValue Milx::CLI::ServerCommand::start_server()
{
	if (SERVER_PID_FILE.exists()) {
		std::cout << "A server is already started!" << std::endl;
		return CLI_FAIL;
	} else {
		if (!wait) {
			if (fork()) return CLI_SUCCESS; // finish parent
			else setsid(); // detach
		}

		Milx::Application app;

		std::ofstream log(SERVER_LOG_FILE.str().c_str(), std::ios_base::app);
		app.logger(new Milx::Logger(log));

		Milx::ProjectLoader::load(app, _path);
		Milx::Path::initialize_mime_magic();
		// TODO make it changeable somehow
		Milx::Path::initialize_mime_map(Milx::Path("/etc/mime.types"));
		_daemon = new Milx::Server::Daemon(app, port);
		_daemon->public_dir(new Milx::Path(_path / "public"));
		_daemon->start();

		if (wait) { // doesn't detach
			getchar();
			_daemon->stop();
		} else {
			struct sigaction action;
			action.sa_handler = &Milx::CLI::ServerCommand::_stop_server;
			sigaction(SIGTERM, &action, NULL);

			std::ofstream pid(SERVER_PID_FILE.str().c_str());
			pid << getpid();
			pid.close();

			while(_daemon->running()); //  if !SIGALRM received
		}

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
