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

#include <regex.h>
#include <string>
#include <vector>

#include <milx/routing.h>
#include <milx/http/call.h>

void milx::Routing::route(const std::string& regex, const std::string& cont,
                          const std::string& action) {
  milx::RegexRoute route;
  if (regcomp(&route.regex, regex.c_str(), REG_EXTENDED|REG_NOSUB) == 0) {
    route.controller = cont;
    route.action = action;
    this->routes.push_back(route);
  } else {
    // TODO(xjunior) report error on route
  }
}

void milx::Routing::translate_call(milx::http::Call& call) {
  std::vector<milx::RegexRoute>::iterator route;
  const char *path = call.path().c_str();

  for (route = routes.begin(); route != routes.end(); ++route) {
    if (regexec(&route->regex, path, (size_t) 0, NULL, 0) == 0) {
      call.controller(route->controller);
      call.action(route->action);

      return;
    }
  }

  throw milx::NoRouteFound();
}

