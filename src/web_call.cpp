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

#include <ostream>
#include "web_call.hpp"
#include "path.hpp"

Milx::WebCall::WebCall(Milx::CallMethod method, std::string path) :
	_method(method),
	_path(path),
	_content_type("text/html; charset=utf-8"),
	_status(200)
{
	_content.str("");
	_content.flush();
	_content.clear();
}

Milx::WebCall::~WebCall()
{
	delete _file_content;
}

void Milx::WebCall::content(const Milx::Path& path)
{
	if (path.exists() && path.stat().is_file()) {
		content_type(path.type());
		_file_content = new Milx::Path(path.str());
	} else throw Milx::NoRouteFound();
}

const Milx::Path * const Milx::WebCall::file_content() const
{
	return _file_content;
}

std::ostream& operator<<(std::ostream& os, const Milx::WebCall& call)
{
	os << call.path() << std::endl;
	os << "\tController: " << call.controller() << std::endl;
	os << "\tAction: " << call.action() << std::endl;
	os << "\tParams: " << call.params.size() << std::endl;
	os << "\tStatus" << call.status() << std::endl;
	os << "\tContent Type: " << call.content_type() << std::endl;

	return os;
}
