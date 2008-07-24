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

#ifndef MILX_REQUEST_H
#define MILX_REQUEST_H

#include <string>

namespace Milx
{
    /**
     * An abstract class to interface a Request in many ways.
     * This class is extended in Milx::CGI::Request, for example.
     * \see Milx::CGI::Request
     */
    class Request
    {
        /**
         * The requested action name
         */
        std::string _action;
        /**
         * The requested controller name
         */
        std::string _controller;
    public:
        //Request(std::string path);
        /**
         * \return the requested action name
         */
        std::string action() { return _action; }
        void action(std::string act_name) { _action = act_name; }
        /**
         * \return the requested controller name
         */
        std::string controller() { return _controller; }
        void controller(std::string ctrl_name) { _controller = ctrl_name; }

        // abstract methods
        /**
         * \return the accept HTTP header
         */
        virtual std::string accept()=0;
        /**
         * \return Accept-Charset HTTP header
         */
        virtual std::string acceptCharset()=0;
        virtual std::string acceptEncoding()=0;
        virtual std::string acceptLanguage()=0;
        virtual std::string from()=0;
        virtual std::string host()=0;
        virtual std::string pragma()=0;
        virtual std::string referer()=0;
        virtual std::string userAgent()=0;
        virtual std::string queryString()=0;
        virtual std::string remoteAddress()=0;
        virtual std::string remoteHost()=0;
        virtual std::string contentType()=0;
    };
}

#endif
