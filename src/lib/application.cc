/*
 * Copyright 2010 Carlos Junior
 *
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

#include <dlfcn.h>

#include <vector>

#include <milx/application.h>
#include <milx/http/call.h>
#include <milx/controller.h>
#include <milx/action_callback.h>
#include <milx/path.h>
#include <milx/plugins.h>

milx::Application::Application()
  : _logger(new Logger()), _plugins(*this) {
}

void milx::Application::dispatch(milx::http::Call& call) {
  this->logger().info() << "Request to" << call.path();

  try {
    this->_routes.translateCall(call);

    milx::ControllerPtr ctrlobj = this->_controllers[call.controller()];

    if (ctrlobj != NULL) {
      milx::ActionCallback::CallbackBasePtr actobj = ctrlobj->action(call.action());
      if (actobj != NULL) {
	actobj->call(call);
        return;
      }
    }

    throw milx::UnimplementedRoute();
  } catch(milx::NoRouteFound e) {
    call.status(404);
    this->logger().error() << "Milx::NoRouteFound caught";
  } catch(milx::UnimplementedRoute e) {
    call.status(501);
    this->logger().error() << "Milx::UnimplementedRoute caught";
  } catch(std::exception e) {
    call.status(500);
    this->logger().error() << "Exception caught: " << e.what();
  } catch(...) {
    call.status(500);
    this->logger().error() << "Unknown exception caught";
  }

  // FIXME(xjunior) this->logger().info() << call;
}

void milx::Application::controller(milx::Controller *controller, std::string name) {
  _controllers[name] = milx::ControllerPtr(controller);
}

void milx::Application::load_plugins() {
  for (milx::Path::List::iterator begin = _plugins_path.begin();
        begin != _plugins_path.end();
        begin++) {
    milx::Path::List solist = milx::Path::ls((*begin / "*.so").str().c_str());
    milx::Path::List::iterator it;

    for (it = solist.begin(); it != solist.end(); it++) {
      try {
        if ((*it).stat().is_file()) {
          this->logger().info() << "Loading plugin" << (*it).str();
          _plugins.load(*it);
          this->logger().info() << "Load Successfull!";
        }
      } catch(const std::exception &ex) {
        this->logger().error() << ex.what();
      }
    }
  }
}

milx::Application::~Application() {
}

