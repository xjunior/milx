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

#include <vector>

#include "application.h"
#include "http/call.h"
#include "controller.h"
#include "shared_module.h"
#include "action_callback.h"
#include "path.h"

milx::Application::Application()
  : _logger(new Logger()), milx::Module(*this) {
}

void milx::Application::load_module(const milx::Path &file) {
  this->logger().info() << "Loading module " << file.str().c_str();
  _modules.push_back(new milx::SharedModule(*this, file));
}

void milx::Application::dispatch(milx::http::Call& call) {
  this->logger().info() << "Request to " << call.path();

  try {
    for (std::vector<Module*>::const_iterator it = _modules.begin();
          it != _modules.end(); it++)
      try {
        (*it)->dispatch(call);
      } catch(milx::NoRouteFound) { continue; }

    milx::Module::dispatch(call);
  } catch(milx::NoRouteFound e) {
    call.status(400);
    this->logger().error() << "Milx::NoRouteFound caught";
  } catch(milx::UnimplementedRoute e) {
    call.status(500);
    this->logger().error() << "Milx::UnimplementedRoute caught";
  } catch(std::exception e) {
    call.status(500);
    this->logger().error() << "Exception caught: " << e.what();
  } catch(...) {
    call.status(500);
    this->logger().error() << "Unknown exception caught";
  }

  // TODO(xjunior) this->logger().info() << call;
}

milx::Application::~Application() {
  if (_modules.size() > 0)
    for (register int i = 0; i < _modules.size(); i++)
      delete _modules[i];
}

void milx::Application::add_module(milx::Module *mod) {
  _modules.push_back(mod);
}

