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
    	char *env = getenv("HTTP_ACCEPT");
	return ((env == NULL)? "" : env);
}

std::string Milx::CGI::Request::acceptCharset()
{
    	char *env = getenv("HTTP_ACCEPT_CHARSET");
	return ((env == NULL)? "" : env);
}

std::string Milx::CGI::Request::acceptEncoding()
{
    	char *env = getenv("HTTP_ACCEPT_ENCODING");
	return ((env == NULL)? "" : env);
}

std::string Milx::CGI::Request::acceptLanguage()
{
    	char *env = getenv("HTTP_ACCEPT_LANGUAGE");
	return ((env == NULL)? "" : env);
}

std::string Milx::CGI::Request::from()
{
    	char *env = getenv("HTTP_FROM");
	return ((env == NULL)? "" : env);
}

std::string Milx::CGI::Request::host()
{
    	char *env = getenv("HTTP_HOST");
	return ((env == NULL)? "" : env);
}

std::string Milx::CGI::Request::pragma()
{
    	char *env = getenv("HTTP_PRAGMA");
	return ((env == NULL)? "" : env);
}

std::string Milx::CGI::Request::referer()
{
    	char *env = getenv("HTTP_REFERER");
	return ((env == NULL)? "" : env);
}

std::string Milx::CGI::Request::userAgent()
{
	char *env = getenv("HTTP_USER_AGENT");		
    	return ((env == NULL)? "" : env);
}

std::string Milx::CGI::Request::queryString()
{
    	char *env = getenv("QUERY_STRING");
	return ((env == NULL)? "" : env);
}

std::string Milx::CGI::Request::remoteAddress()
{
    	char *env = getenv("REMOTE_ADDRESS");
	return ((env == NULL)? "" : env);
}

std::string Milx::CGI::Request::remoteHost()
{
    	char *env = getenv("REMOTE_HOST");
	return ((env == NULL)? "" : env);
}

std::string Milx::CGI::Request::contentType()
{
    	char *env = getenv("CONTENT_TYPE");
	return ((env == NULL)? "" : env);
}

std::string Milx::CGI::Request::cookie() 
{
	char *env = getenv("HTTP_COOKIE");
	return ((env == NULL)? "" : env);	
}
