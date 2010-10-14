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

#ifndef MILX_ROUTING_H
#define MILX_ROUTING_H

#include <regex.h>

#include <string>
#include <vector>

namespace milx {
  namespace http { class Call; }

  struct RegexRoute {
    regex_t regex;
    std::string controller;
    std::string action;
  };

  // TODO(xjunior) create Routing namespace and RoutingCollection
  class Routing {
    std::vector<RegexRoute> routes;
  public:
    void route(const std::string& regex, const std::string& controller,
								const std::string& action);
    /**
     * Translate the Request discovering which controller/action it's
     * requesting
     * \param request
     * \return a reference to the controller
     */
    void translateCall(http::Call&);
  };

  class NoRouteFound {};
  class UnimplementedRoute {};
}

#endif  // MILX_ROUTING_H
