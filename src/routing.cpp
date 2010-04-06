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

#include <regex.h>
#include "routing.hpp"
#include "web_call.hpp"

void Milx::Routing::route(std::string regex, std::string controller, std::string action)
{
	Milx::RegexRoute route;
	if (regcomp(&route.regex, regex.c_str(), REG_EXTENDED|REG_NOSUB) == 0) {
		route.controller = controller;
		route.action = action;
		this->routes.push_back(route);
	} else {
		// report error
	}
}

bool Milx::Routing::translateCall(Milx::WebCall& call)
{
	std::vector<Milx::RegexRoute>::iterator iroutes;
	const char *path = call.path().c_str();
	bool result = false;

	for (iroutes = this->routes.begin(); iroutes != routes.end() && !result; ++iroutes) {
		if (regexec(&iroutes->regex, path, (size_t) 0, NULL, 0)  == 0) {
			call.controller(iroutes->controller);
			call.action(iroutes->action);
            
			result = true;
		}
	}

	return result;
}

