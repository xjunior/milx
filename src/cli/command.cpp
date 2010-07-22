#include "command.hpp"
#include <cstring>
#include <iostream>

Milx::CLI::ReturnValue Milx::CLI::Command::run(int argc, char* argv[])
{
	if (strcmp(argv[1], "help") == 0 || strcmp(argv[1], "?") == 0)
		show_help();
	else {
		char** argvv = new char*[argc-1];
		for (int i = 1; i < argc; i++)
			argvv[i-1] = argv[i];

		ReturnValue r = this->main(argc-1, argvv);
		if (r == CLI_SHOW_HELP) this->show_help();

		return CLI_SHOW_HELP;
	}
}

void Milx::CLI::Command::show_help()
{
	if (strlen(description()) > 0) std::cout << description() << std::endl;
	if (strlen(help()) > 0) std::cout << help() << std::endl;
	if (installed.size() > 0) {
		std::cout << std::endl << "Installed commands:" << std::endl;
		for (std::vector<Command*>::iterator it = installed.begin(); it != installed.end(); it++)
			std::cout << (*it)->command() << "\t: " << (*it)->description() << std::endl;
	}
}

void Milx::CLI::Command::install(Command *c)
{
	installed.push_back(c);
}

const Milx::CLI::Command* const Milx::CLI::Command::command(std::string name) const
{
	for (int i = 0; i < installed.size(); i++)
		if (name.compare(installed[i]->command()) == 0) return installed[i];

	throw CommandNotFound();
}
