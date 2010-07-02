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
			virtual ReturnValue main(int, char**);
			ReturnValue start_server(int);
			ReturnValue stop_server();
			static void _stop_server(int);
			static Milx::Server::Daemon *_daemon;

		public:
			virtual void show_help();
			virtual const char* description();
		};
	}
}

