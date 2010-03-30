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

#include <magic.h>
#include <iostream>
#include "controller.hpp"
#include "view/renderer.hpp"
#include "module.hpp"

Milx::Actiont Milx::Controller::action(std::string name)
{
	std::map<std::string, Milx::Actiont>::iterator iter = actionsCallbacks.find(name);
	if (iter != actionsCallbacks.end()) return iter->second;
	else return NULL;
}

void Milx::Controller::registerAction(Milx::Actiont mptr, std::string name)
{
	actionsCallbacks.insert( make_pair(name, mptr) );
}

void Milx::Controller::module(Milx::Module* mod)
{
	this->_module = mod;
}

Milx::Module& Milx::Controller::module()
{
	return *this->_module;
}

/*Milx::Response* Milx::Controller::view_response(std::string view)
{
	Milx::Response* resp = new Milx::Response;
	boost::filesystem::path view_path = module().viewsPath() / view;
	resp->content = Milx::View::Renderer::render_file(view_path);

	// FIXME: The code bellow should not be here
	magic_t cookie;
	if (cookie = magic_open(MAGIC_MIME)) {
		if (magic_load(cookie, NULL) == 0)
			resp->headers["Content-Type"] = magic_file(cookie, view_path.string().c_str());

		magic_close(cookie);
	}
    
	return resp;
}*/

