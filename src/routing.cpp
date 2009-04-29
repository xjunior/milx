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
#include "routing.hpp"
#include "request.hpp"

void Milx::Routing::route(std::string regex, std::string controller, std::string action)
{
    Milx::RegexRoute route;
    route.regex = boost::regex(regex);
    route.controller = controller;
    route.action = action;
    this->routes.push_back(route);
}

bool Milx::Routing::translateRequest(Milx::Request& req)
{
    std::vector<Milx::RegexRoute>::iterator iroutes;
    boost::match_results<std::string::const_iterator> what;
    std::string::const_iterator begin = req.fullPath().begin(), end = req.fullPath().end();

    for (iroutes = this->routes.begin(); iroutes != routes.end(); ++iroutes)
        if (regex_search(begin, end, what, iroutes->regex))
        {
            req.controller(iroutes->controller);
            req.action(iroutes->action);
            
            return true;
        }

    return false;
}

