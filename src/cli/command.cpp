#include "command.hpp"

std::map<std::string, Milx::CLI::Command*> Milx::CLI::Command::installed;

Milx::CLI::ReturnValue Milx::CLI::Command::run(int argc, char* argv[])
{
	char** argvv = new char*[argc-1];
	for (int i = 1; i < argc; i++)
		argvv[i-1] = argv[i];

	ReturnValue r = this->main(argc-1, argvv);
	if (r == CLI_SHOW_HELP) this->show_help();

	return r;
}

