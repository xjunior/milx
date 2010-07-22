/*
 * This file is part of Milx-Server.
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

#ifndef MILX_SERVER_H
#define MILX_SERVER_H

// MicroHTTPD dependency and tree
#include <cstdlib>
#include <cstring>
#include <stdint.h>
#include <cstdarg>
#include <sys/socket.h>
#include <microhttpd.h>

#include <string>
#include "../application.hpp"

#define MILX_SERVER_NAME "Milx Server v1.0"

namespace Milx
{
	class WebCall;

	namespace Server
	{
		class Daemon
		{
			Milx::Application &_app;
			int _port;
			bool _running;
			struct MHD_Daemon *_mhdaemon;
                        const Milx::Path *_public;

			static int _connection_dispatcher(void *, struct MHD_Connection *,
							const char *, const char *,
							const char *, const char *,
							size_t *, void **);

			static int _copy_values(void *, enum MHD_ValueKind,
                            const char *, const char *);
                        static int _post_values(void *, enum MHD_ValueKind,
                            const char *, const char *, const char *,
                            const char *, const char *, uint64_t, size_t);
			static int _queue_response(struct MHD_Connection *, Milx::WebCall &);
		public:
			std::vector<std::string> index;
			Daemon(Milx::Application&, int);
                        ~Daemon();
			void start();
			void stop();
                        void public_dir(const Milx::Path* pub) { _public = pub; }
                        const Milx::Path* public_dir() { return _public; }
                        Milx::Application& application() { return _app; }
			bool running() { return _running; }
		};
	}
}

#endif
