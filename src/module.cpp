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

#include "module.hpp"
#include "routing.hpp"
#include "application.hpp"

Milx::Module::Module(Milx::Application& app, std::string name)
	: _app(app), _name(name), _views_path(Milx::Path::cwd())
{ }

std::string Milx::Module::name()
{
	return _name;
}

void Milx::Module::name(std::string name)
{
	_name = name;
}

Milx::Path Milx::Module::viewsPath()
{
	return _views_path;
}

void Milx::Module::viewsPath(const Milx::Path &vp)
{
	_views_path = vp;
}

void Milx::Module::controller(Milx::Controller* c, std::string name)
{
	c->module(this);
	this->_controllers[name] = c;
}

Milx::Controller* Milx::Module::controller(std::string name)
{
	return this->_controllers[name];
}

Milx::Routing& Milx::Module::routes()
{
	return _routes;
}

void Milx::Module::dispatch(Milx::WebCall& call)
{
	this->routes().translateCall(call);

	Milx::Controller* ctrlobj = this->controller(call.controller());

	if (ctrlobj != NULL) {
		Milx::ActionCallback::CallbackBase* actobj = ctrlobj->action(call.action());
		if (actobj != NULL) {
			actobj->call(call);
			return;
		}
	}

	throw Milx::UnimplementedRoute();
}

