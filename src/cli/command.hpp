#ifndef MILX_CLI_COMMAND_HPP
#define MILX_CLI_COMMAND_HPP

#include <map>
#include <string>

#define MILX_COMMAND_SUCCESS 0
#define MILX_COMMAND_ERROR 1

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
			virtual ReturnValue main(int, char**)=0;
		public:
			virtual void show_help()=0;
			virtual const char* description()=0;
			ReturnValue run(int, char**);

			static std::map<std::string, Command*> installed;
		};
	}
}

#endif
