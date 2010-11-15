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

#ifndef MILX_CLI_SERVER_COMMAND_H
#define MILX_CLI_SERVER_COMMAND_H

#include "command.h"

#include <milx/path.h>

// TODO(xjunior) cross os compatibility, maybe a shipped version

namespace milx {
  namespace server { class Daemon; }

  namespace cli {
    class ServerCommand : public Command {
      milx::Path _path, _output, _mime, _pid;
      bool wait;
      int port;

      static milx::server::Daemon *_daemon;

      ReturnValue main(int, char**);
      ReturnValue start_server();
      ReturnValue stop_server();
      static void _stop_server(int signal);

      void create_pid();
      void bind_stop();
     public:
      ServerCommand();
      const char* help();
      const char* description();
      const char* command();
    };
  }
}

#endif  // MILX_CLI_SERVER_COMMAND_H

