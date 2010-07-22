#ifndef MILX_CLI_COMMAND_HPP
#define MILX_CLI_COMMAND_HPP

#include <vector>
#include <string>

namespace Milx
{
	namespace CLI
	{
		enum ReturnValue
		{
			CLI_SUCCESS = 0,
			CLI_FAIL = 1,
			CLI_SHOW_HELP = 2
		};

		class Command
		{
			std::vector<Command*> installed;
			virtual ReturnValue main(int, char**)=0;
		public:
			void show_help();
			virtual const char* help()=0;
			virtual const char* description()=0;
			ReturnValue run(int, char**);
			virtual const char* command()=0;
		protected:
			void install(Command*);
			const Command* const command(std::string) const;
		};

		class CommandNotFound : public std::exception { };
	}
}

#endif
