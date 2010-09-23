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

#include <fstream>
#include <csignal>
#include "create_command.h"

milx::cli::ReturnValue milx::cli::CreateCommand::main(int argc, char* argv[]) {
  return CLI_SHOW_HELP;
}

const char* milx::cli::CreateCommand::description() {
  return "create source structures";
}

const char* milx::cli::CreateCommand::command() {
  return "create";
}

const char* milx::cli::CreateCommand::help() {
  return "create [command] [options]";
}

