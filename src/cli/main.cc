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

#include <iostream>

#include "command.h"
#include "server_command.h"
#include "create_command.h"

class MainCommand : public milx::cli::Command {
 public:
  const char* description() {
    return "milx utility is your main entry for the Milx world";
  }
  const char* command() { return ""; }
  const char* help() { return "milx [command]"; }
};

int main(int argc, char* argv[]) {
  MainCommand m;
  m.install(new milx::cli::ServerCommand);
  m.install(new milx::cli::CreateCommand);
  return m.run(argc, argv);
}

