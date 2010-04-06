#include <iostream>
#include <sstream>
#include <string.h>
#include "command.hpp"
#include "server_command.hpp"

inline void install_commands()
{
	Milx::CLI::Command::installed["server"] = new Milx::CLI::ServerCommand;
}

int main(int argc, char* argv[])
{
	install_commands();

	if (argc >= 2) {
		Milx::CLI::Command *cmd = Milx::CLI::Command::installed[argv[1]];
		if (cmd) return cmd->run(argc, argv);
		else {
			std::cout << "Command not found: " << argv[1] << std::endl;
		}
	} else {
		std::cout << "Provide some command, please." << std::endl;
	}
}

