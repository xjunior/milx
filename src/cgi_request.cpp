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

#include "cgi_request.h"

std::string Milx::CGI::Request::accept()
{
    return getenv("HTTP_ACCEPT");
}

std::string Milx::CGI::Request::acceptCharset()
{
    return getenv("HTTP_ACCEPT_CHARSET");
}

std::string Milx::CGI::Request::acceptEncoding()
{
    return getenv("HTTP_ACCEPT_ENCODING");
}

std::string Milx::CGI::Request::acceptLanguage()
{
    return getenv("HTTP_ACCEPT_LANGUAGE");
}

std::string Milx::CGI::Request::from()
{
    return getenv("HTTP_FROM");
}

std::string Milx::CGI::Request::host()
{
    return getenv("HTTP_HOST");
}

std::string Milx::CGI::Request::pragma()
{
    return getenv("HTTP_PRAGMA");
}

std::string Milx::CGI::Request::referer()
{
    return getenv("HTTP_REFERER");
}

std::string Milx::CGI::Request::userAgent()
{
    return getenv("HTTP_USER_AGENT");
}

std::string Milx::CGI::Request::queryString()
{
    return getenv("QUERY_STRING");
}

std::string Milx::CGI::Request::remoteAddress()
{
    return getenv("REMOTE_ADDRESS");
}

std::string Milx::CGI::Request::remoteHost()
{
    return getenv("REMOTE_HOST");
}

std::string Milx::CGI::Request::contentType()
{
    return getenv("CONTENT_TYPE");
}
