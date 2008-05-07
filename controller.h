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

#ifndef MILX_CONTROLLER_H
#define MILX_CONTROLLER_H

#include <string>
// Foward declaration won't work for request
#include "request.h"

namespace Milx
{
    class Application;
    namespace CGI
    {
        class Response;
    }
    class Controller
    {
        protected:
            Application *application;
        public:
            virtual CGI::Response callAction(std::string)=0;
            CGI::Request& request()
            {
                return CGI::Request::instance();
            }
            void setApplication(Application *a)
            {
                application = a;
            }
    };
}

#endif
