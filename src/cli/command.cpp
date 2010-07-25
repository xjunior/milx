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

#include "command.hpp"
#include <cstring>
#include <iostream>

Milx::CLI::ReturnValue Milx::CLI::Command::run(int argc, char* argv[])
{
	try {
		return command(argv[1])->run(argc, argv);
	} catch (Milx::CLI::CommandNotFound) {
		if (strcmp(argv[argc-1], "help") == 0 || strcmp(argv[argc-1], "?") == 0) {
			show_help();
			return CLI_SUCCESS;
		}

		char** argvv = new char*[argc-1];
		for (int i = 1; i < argc; i++)
			argvv[i-1] = argv[i];

		ReturnValue r = this->main(argc-1, argvv);
		if (r == CLI_SHOW_HELP) this->show_help();

		return r;
	}
}

void Milx::CLI::Command::show_help()
{
	if (strlen(description()) > 0) std::cout << description() << std::endl;
	if (strlen(help()) > 0) std::cout << help() << std::endl;
	if (installed.size() > 0) {
		std::cout << std::endl << "Installed commands:" << std::endl;
		for (std::list<Command*>::iterator it = installed.begin(); it != installed.end(); it++)
			std::cout << (*it)->command() << "\t: " << (*it)->description() << std::endl;
	}
}

void Milx::CLI::Command::install(Command *c)
{
	installed.push_back(c);
}

Milx::CLI::Command* const Milx::CLI::Command::command(const std::string& name) const
{
	for (std::list<Command*>::const_iterator it = installed.begin(); it != installed.end(); it++)
		if (name.compare((*it)->command()) == 0) return *it;

	throw CommandNotFound();
}
