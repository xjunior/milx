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

#ifndef MILX_WEB_CALL_H
#define MILX_WEB_CALL_H

#include <string>
#include <sstream>
#include <map>

namespace Milx
{
	enum CallMethod	{ METHOD_POST, METHOD_GET, METHOD_PUT, METHOD_DELETE };

	class Path;

	class WebCall
	{
	        CallMethod _method;
		std::string _path;
		std::stringstream _content;
		std::string _controller;
		std::string _action;
		std::string _content_type;
		int _status;
	    public:
	        WebCall(CallMethod, std::string);

		CallMethod method() { return _method; }
		const std::string& path() { return _path; }
		const std::string& controller() { return _controller; }
		void controller(std::string c) { _controller = c; }
		const std::string& action() { return _action; }
		void action(std::string a) { _action = a; }

		std::map<std::string, std::string> params;
		
		// content
		void content_type(std::string s) { _content_type = s; }
		std::string content_type() { return _content_type; }
		void status(int s) { _status = s; }
		int status() { return _status; }
		std::stringstream& content() { return _content; }
		void content(const Milx::Path&);
		// void content(Milx::View);
	};
}

#endif
