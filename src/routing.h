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

#ifndef MILX_ROUTING_H
#define MILX_ROUTING_H

#include <map>
#include <string>
#include "controller.h"

namespace Milx
{
    class Request;

    class Routing
    {
        /**
         * The controllers held by the application.
         */
        std::map<std::string, Controller*> controllers;
    public:
        /**
         * Register the route to a controller.
         * \param the controller Instance
         * \param the controller name
         */
        void controller(Controller*, std::string);
        /**
         * Retrieve a registered controller instance.
         * \param the controller name
         */
        Controller* controller(std::string);
        /**
         * Translate the Request discovering which controller/action it's
         * requesting
         * \param request
         * \return a reference to the controller
         */
        Controller* translateRequest(Request*);
    };
}

#endif
