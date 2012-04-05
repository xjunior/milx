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

#include "server_command.h"

#include <fstream>
#include <iostream>
#include <csignal>
#include <string>
#include <cstring>

#include <milx/server/daemon.h>
#include <milx/application.h>
#include <milx/milx.h>

#define SERVER_DEFAULT_MIME "mime.types"
#define SERVER_LOG_FILE "milx-server.log"
#define SERVER_PID_FILE "milx-server.pid"

milx::server::Daemon *milx::cli::ServerCommand::_daemon;

milx::cli::ServerCommand::ServerCommand()
  : Command(), wait(0), port(8888),
    _path(milx::Path::cwd()),
    _output(_path / SERVER_LOG_FILE),
    _pid(_path / SERVER_PID_FILE),
    _mime(milx::home() / SERVER_DEFAULT_MIME) {
}

milx::cli::ReturnValue milx::cli::ServerCommand::main(int argc, char* argv[]) {
  if (argc >= 2) {
    int opt;
    char *cmd = argv[1];
    while ((opt = getopt(argc, argv, "wp:d:o:m:")) != -1) {
      switch (opt) {
      case 'w': wait = true; break;
      case 'p': port = atoi(optarg); break;
      case 'd':
        _path = optarg;
        _pid = _path / SERVER_PID_FILE;
        // FIXME _output and _mime might become invalid if using default
        break;
      case 'o': _output = optarg; break;
      case 'm': _mime = optarg; break;
      }
    }

    if (strcmp(cmd, "start") == 0) {
      return start_server();
    } else if (strcmp(cmd, "stop") == 0) {
      return stop_server();
    } else if (strcmp(cmd, "restart") == 0) {
      if (stop_server() == CLI_SUCCESS)
        return start_server();
      else
        return CLI_FAIL;
    }
  }
  return CLI_SHOW_HELP;
}

const char* milx::cli::ServerCommand::help() {
  return "server [start|stop|restart] [options]\n" \
    "-d <path>\tproject root (default to current)\n"\
    "-w\t\tdon't go to background, wait until you press any key to finish\n"\
    "-p <port>\tport (default to 8888)";
}

const char* milx::cli::ServerCommand::description() {
  return "Manage milx built-in server";
}

const char* milx::cli::ServerCommand::command() {
  return "server";
}

milx::cli::ReturnValue milx::cli::ServerCommand::start_server() {
  if (_pid.exists()) {
    std::cerr << "A server is already started!" << std::endl;
    return CLI_FAIL;
  } else {
    if (!wait)
      if (fork()) return CLI_SUCCESS;  // finish parent proc
      else setsid(); // detach

    create_pid();
    bind_stop();

    milx::Application app;
    std::ofstream logstream(_output.str().c_str(), std::ios_base::app);
    milx::Logger log(logstream);
    app.logger(&log);

    app._plugins_path.push_back(milx::home() / "plugins");
    app._plugins_path.push_back(_path);
    app.load_plugins();

    milx::Path::initialize_mime_magic();
    milx::Path::initialize_mime_map(_mime);

    _daemon = new milx::server::Daemon(app, port);
    _daemon->public_dir(milx::Path(_path / "public"));

    if (_daemon->start())
      if (wait) {
	std::cin.get();
	_daemon->stop();
      } else
        while (_daemon->running());  // if !SIGTERM received
    else
      std::cerr << "Failed to start server" << std::endl;

    unlink(_pid.str().c_str());
    logstream.close();

    return CLI_SUCCESS;
  }
}

milx::cli::ReturnValue milx::cli::ServerCommand::stop_server() {
  if (_pid.exists()) {
    std::ifstream fstream(_pid.str().c_str());
    std::string pid;
    fstream >> pid;
    fstream.close();
    std::cout << "Terminating server on pid " << pid << std::endl;
    kill(atoi(pid.c_str()), SIGTERM);
  }

  return CLI_SUCCESS;
}

void milx::cli::ServerCommand::_stop_server(int /* signal */) {
  _daemon->stop();
  return;
}

void milx::cli::ServerCommand::create_pid() {
  std::ofstream pid(_pid.str().c_str());
  pid << getpid();
  pid.close();
}

void milx::cli::ServerCommand::bind_stop() {
  struct sigaction action;
  action.sa_handler = &milx::cli::ServerCommand::_stop_server;
  sigaction(SIGTERM, &action, NULL);
}

