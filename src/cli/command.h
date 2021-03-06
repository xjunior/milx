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

#ifndef MILX_CLI_COMMAND_H
#define MILX_CLI_COMMAND_H

#include <list>
#include <string>

namespace milx {
  namespace cli {
    enum ReturnValue {
      CLI_SUCCESS = 0,
      CLI_FAIL = 1,
      CLI_SHOW_HELP = 2
    };

    class Command {
      std::list<Command*> installed;
      virtual ReturnValue main(int, char**) { return milx::cli::CLI_SHOW_HELP; }
     public:
      void install(Command* cmd);
      Command* const command(const std::string&) const;
      virtual const char* help()=0;
      virtual const char* description()=0;
      virtual const char* command()=0;
      void show_help();
      ReturnValue run(int, char**);
    };

    class CommandNotFound : public std::exception { };
  }
}

#endif  // MILX_CLI_COMMAND_H
