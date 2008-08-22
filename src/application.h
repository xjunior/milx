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

#ifndef MILX_APPLICATION_H
#define MILX_APPLICATION_H

#include "routing.h"
#define MILX_APPLICATION_LOADABLE "../build/routes.so"

namespace Milx
{
    class Response;
    class Request;

    /**
     * The Milx::Application class handle the currently running application.
     *
     * This class is responsible by loading the controllers from the current
     * project and handle the application.
     *
     * The application rendering and response are made by the handlers (CGI,
     * FCGI, Apache, etc).
     */
    class Application
    {
        Milx::Routing routes;
        void* loader;
    public:
        /**
         * Constructor for application. No argument needed (yet).
         */
        Application();
        /**
         * Destructor for application.
         */
        ~Application();
        /**
         * Dispatch a request to the correct controller/action
         * \param req is the request to be dispatched
         * \return a http response
         */
        Milx::Response* dispatch(Milx::Request*);
    private:
        void loadRoutes();
    };

    /**
     * Class thrown when the routes file was not found or the
     * routing function is not defined.
     */
    class RoutesNotFound {};
}

#endif
