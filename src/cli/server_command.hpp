/*
 * This file is part of Milx.
 *
 * Milx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Milx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Milx.  If not, see <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

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
			int wait;
			int port;

			static Milx::Server::Daemon *_daemon;

			ReturnValue main(int, char**);
			ReturnValue start_server();
			ReturnValue stop_server();
			static void _stop_server(int);
		public:
			ServerCommand() : Command(), wait(0), port(8888), _path(Milx::Path::cwd()) { }
			const char* help();
			const char* description();
			const char* command();
		};
	}
}
