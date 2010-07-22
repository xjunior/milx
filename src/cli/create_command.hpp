#include "command.hpp"

namespace Milx
{
	namespace CLI
	{
		class CreateCommand : public Command
		{
			ReturnValue main(int, char**);
		public:
			const char* help();
			const char* description();
			const char* command();
		};
	}
}

