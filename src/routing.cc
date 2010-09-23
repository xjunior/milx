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

#include "routing.h"
#include "http/call.h"

void milx::Routing::route(std::string regex, std::string controller,
                          std::string action) {
  milx::RegexRoute route;
  if (regcomp(&route.regex, regex.c_str(), REG_EXTENDED|REG_NOSUB) == 0) {
    route.controller = controller;
    route.action = action;
    this->routes.push_back(route);
  } else {
    // TODO(xjunior) report error on route
  }
}

void milx::Routing::translateCall(milx::http::Call& call) {
  std::vector<milx::RegexRoute>::iterator iroutes;
  const char *path = call.path().c_str();
  bool result = false;

  for (iroutes = this->routes.begin();
        iroutes != routes.end() && !result; ++iroutes) {
    if (regexec(&iroutes->regex, path, (size_t) 0, NULL, 0) == 0) {
      call.controller(iroutes->controller);
      call.action(iroutes->action);

      result = true;
    }
  }

  if (!result) throw milx::NoRouteFound();
}
