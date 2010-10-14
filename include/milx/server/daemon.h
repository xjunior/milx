/*
 * Copyright 2010 Carlos Junior
 *
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

#ifndef MILX_SERVER_DAEMON_H
#define MILX_SERVER_DAEMON_H

// MicroHTTPD dependency and tree
#include <stdint.h>
#include <sys/socket.h>

#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <microhttpd.h>
#include <string>
#include <vector>

#include <milx/application.h>

namespace milx {
  class Call;

  namespace server {
    class Daemon {
      milx::Application &_app;
      int _port;
      bool _running;
      struct MHD_Daemon *_mhdaemon;
      milx::Path _public;
      bool _use_public;

     public:
      std::vector<std::string> index;
      Daemon(milx::Application&, int);
      ~Daemon();
      bool start();
      bool stop();
      void public_dir(const milx::Path& pub) { _public = pub; }
      void public_dir_enabled(bool enable) { _use_public = enable; }
      bool public_dir_enabled() { return _use_public; }
      const milx::Path& public_dir() { return _public; }
      milx::Application& application() { return _app; }
      bool running() { return _running; }
    };
  }
}

#endif  // MILX_SERVER_DAEMON_H
