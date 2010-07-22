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

#include <iostream>
#include "application.hpp"
#include "web_call.hpp"
#include "controller.hpp"
#include "shared_module.hpp"
#include "action_callback.hpp"
#include "path.hpp"

Milx::Application::Application()
	: Milx::Module(*this)
{
	this->logger(new Milx::Logger(std::cout));
}

void Milx::Application::loadModule(const Milx::Path &file)
{
	this->logger()->info("Loading module " + file.str());
	_modules.push_back(new Milx::SharedModule(*this, file));
}

void Milx::Application::dispatch(Milx::WebCall& call)
{
	this->logger()->info("Request to " + call.path());

	Milx::Controller* ctrlobj;
	bool found;

	if (found = this->routes().translateCall(call))
		ctrlobj = this->controller(call.controller());
	else 
		// it found a route, but if controller STILL NULL, so we try another one
		for (int i = 0; i < _modules.size(); i++)
			if (found = _modules[i]->routes().translateCall(call)) {
				ctrlobj = _modules[i]->controller(call.controller());
				break;
			}

	if (!found) {
		this->logger()->warn("No route found, returning 404");
		call.status(404);
	} else if (ctrlobj == NULL) {
		this->logger()->warn("Route error: Bad controller name: ") << call.controller();
		call.status(500);
	} else {
		this->logger()->info("Routed to ") << call.controller() << "/" << call.action();
		Milx::ActionCallback::CallbackBase* actobj = ctrlobj->action(call.action());
		if (actobj == NULL) {
			this->logger()->warn("Route error: Bad action name: ") << call.action();
			call.status(500);
		} else {
			actobj->call(call);
		}
	}
}

Milx::Application::~Application()
{
	if (_modules.size() > 0)
		for (register int i = 0; i < _modules.size(); i++)
			delete _modules[i];
}

void Milx::Application::logger(Milx::Logger* logger)
{
	if (logger != NULL)
		_logger = logger;
}

void Milx::Application::add_module(Milx::Module *mod)
{
	_modules.push_back(mod);
}

