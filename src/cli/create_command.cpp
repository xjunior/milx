#include <fstream>
#include <csignal>
#include "create_command.hpp"

Milx::CLI::ReturnValue Milx::CLI::CreateCommand::main(int argc, char* argv[])
{
	return CLI_SHOW_HELP;
}

const char* Milx::CLI::CreateCommand::description()
{
	return "create source structures";
}

const char* Milx::CLI::CreateCommand::command()
{
	return "create";
}

const char* Milx::CLI::CreateCommand::help()
{
	return "";
}
