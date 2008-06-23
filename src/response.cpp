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

#include "response.h"
#include <sstream>

Milx::Response::Response(std::string content, int code, std::string format)
{
    _code    = code;
    _content = content;
    _format  = format;
}

std::string Milx::Response::content()
{
    return _content;
}

int Milx::Response::code()
{
    return _code;
}

std::string Milx::Response::format()
{
    return _format;
}

void Milx::Response::setContent(std::string content)
{
    _content = content;
}

void Milx::Response::setCode(int code)
{
    _code = code;
}

void Milx::Response::setFormat(std::string format)
{
    _format = format;
}

std::string Milx::Response::translatedResponseCode()
{
    std::string desc;
    switch (_code)
    {
        // Successful 2xx
        case 200: desc = "OK"; break;
        case 201: desc = "Created"; break;
        case 202: desc = "Accepted"; break;
        case 203: desc = "Non-Authoritative Information"; break;
        case 204: desc = "No Content"; break;
        case 205: desc = "Reset Content"; break;
        case 206: desc = "Partial Content"; break;

        // Redirection 3xx
        case 300: desc = "Multiple Choices"; break;
        case 301: desc = "Moved Permanently"; break;
        case 302: desc = "Found"; break;
        case 303: desc = "See Other"; break;
        case 304: desc = "Not Modified"; break;
        case 305: desc = "Use Proxy"; break;
        case 306: desc = "(Unused)"; // deprecated
        case 307: desc = "Temporary Redirect"; break;

        // Client Error 4xx
        case 400: desc = "Bad Request"; break;
        case 401: desc = "Unauthorized"; break;
        case 402: desc = "Payment Required"; break;
        case 403: desc = "Forbidden"; break;
        case 404: desc = "Not Found"; break;
        case 405: desc = "Method Not Allowed"; break;
        case 406: desc = "Not Acceptable"; break;
        case 407: desc = "Proxy Authentication Required"; break;
        case 408: desc = "Request Timeout"; break;
        case 409: desc = "Conflict"; break;
        case 410: desc = "Gone"; break;
        case 411: desc = "Length Required"; break;
        case 412: desc = "Precondition Failed"; break;
        case 413: desc = "Request Entity Too Large"; break;
        case 414: desc = "Request-URI Too Long"; break;
        case 415: desc = "Unsupported Media Type"; break;
        case 416: desc = "Requested Range Not Satisfiable"; break;
        case 417: desc = "Expectation Failed"; break;

        // Server Error 5xx
        case 500: desc = "Internal Server Error"; break;
        case 501: desc = "Not Implemented"; break;
        case 502: desc = "Bad Gateway"; break;
        case 503: desc = "Service Unavailable"; break;
        case 504: desc = "Gateway Timeout"; break;
        case 505: desc = "HTTP Version Not Supported"; break;

        default: throw BadResponseCode(); break;
    }
    
    std::ostringstream str;
    str << _code;
    str << " ";
    str << desc;

    return str.str();
}

std::string Milx::Response::header()
{
    return "Content-Type: " + format() + "; charset=UTF-8\n"
            "Status: " + translatedResponseCode();
}

std::string Milx::Response::fullResponse()
{
    return header() + "\n\n" + content();
}
