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
    class Request
    {
        std::string _action;
        std::string _controller;
    public:
        //Request(std::string path);
        std::string action() { return "index";}//_action; }
        std::string controller() { return "blog";}//_controller; }

        // abstract methods
        virtual std::string accept()=0;
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
