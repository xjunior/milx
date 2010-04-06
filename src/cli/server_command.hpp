#include "command.hpp"
#include <boost/filesystem/path.hpp>

namespace fs = boost::filesystem;

namespace Milx
{
	namespace Server { class Daemon; }

	namespace CLI
	{
		class ServerCommand : public Command
		{
			fs::path _path;
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

