#include <iostream>
#include "command.hpp"
#include "server_command.hpp"
#include "create_command.hpp"

class MainCommand : public Milx::CLI::Command
{
	Milx::CLI::ReturnValue main(int argc, char** argv) {
		if (argc >= 1) {
			try {
				//return command(std::string(argv[0]))->run(argc, argv);
			} catch (Milx::CLI::CommandNotFound) { }
		}
		return Milx::CLI::CLI_SHOW_HELP;
	}
public:
	MainCommand() {
		install(new Milx::CLI::ServerCommand);
		install(new Milx::CLI::CreateCommand);
	}
	const char* description() { return "milx utility is your main entry for the Milx world"; }
	const char* command() { return ""; }
	const char* help() { return "milx [command]"; }
};

int main(int argc, char* argv[])
{
	return MainCommand().run(argc, argv);
}
