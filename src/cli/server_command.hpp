#include "command.hpp"
#include "../path.hpp"

namespace Milx
{
	namespace Server { class Daemon; }

	namespace CLI
	{
		class ServerCommand : public Command
		{
			Milx::Path _path;
			static Milx::Server::Daemon *_daemon;

			ReturnValue main(int, char**);
			ReturnValue start_server(int);
			ReturnValue stop_server();
			static void _stop_server(int);
		public:
			const char* help();
			const char* description();
			const char* command();
		};
	}
}
