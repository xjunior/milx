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

#include <string>
#include <map>

#include <milx/http/call.h>
#include <milx/module.h>
#include <milx/routing.h>
#include <milx/application.h>

milx::Module::Module(milx::Application& app, std::string name)
  : _app(app), _name(name), _views_path(milx::Path::cwd()) {
}

std::string milx::Module::name() {
  return _name;
}

void milx::Module::name(std::string name) {
  _name = name;
}

milx::Path milx::Module::views_path() {
  return _views_path;
}

void milx::Module::views_path(const milx::Path &vp) {
  _views_path = vp;
}

void milx::Module::controller(milx::ControllerPtr c, std::string name) {
  c->module(this);
  this->_controllers[name] = c;
}

milx::ControllerPtr milx::Module::controller(std::string name) {
  return this->_controllers[name];
}

milx::Routing& milx::Module::routes() {
  return _routes;
}

// FIXME modules should not dispatch, low cohesion
void milx::Module::dispatch(milx::http::Call& call) {
  this->routes().translateCall(call);

  milx::ControllerPtr ctrlobj = this->controller(call.controller());

  if (ctrlobj != NULL) {
    milx::ActionCallback::CallbackBasePtr actobj = ctrlobj->action(call.action());
    if (actobj != NULL) {
      actobj->call(call);
      return;
    }
  }

  throw milx::UnimplementedRoute();
}

std::string milx::Module::controller_name(Controller* c) {
  std::map<std::string, milx::ControllerPtr>::const_iterator it;
  for (it = _controllers.begin(); it != _controllers.end(); it++)
    if (it->second.get() == c)
      return it->first;

  // TODO(xjunior) throw exception
  return "";
}

