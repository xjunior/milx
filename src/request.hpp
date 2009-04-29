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
#include <map>
#include <vector>
//#include "cookie.h"

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
        std::string _full_path;
        std::string _method;
        std::string _version;
        /**
         * The list of cookies sent by browser
         */
        // CookieList _cookies;
    public:
        Request(std::string, std::string, std::string);
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

        // CookieList &cookies() { return _cookies; }
        std::map<std::string, std::string> headers;
        std::string fullPath() { return _full_path; }
        std::string method() { return _method; }
        std::string HTTPVersion() { return _version; }

        std::string uri;
        std::vector<std::string> path;

        static Milx::Request* parse(const std::string);
    protected:
        virtual std::string cookieHeader() { return ""; }
    };
}

#endif
