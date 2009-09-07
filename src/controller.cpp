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

#include "controller.hpp"
#include "request.hpp"
#include "response.hpp"
#include "view.hpp"
#include "module.hpp"

Milx::Response* Milx::Controller::dispatch(Milx::Request &req)
{
    std::map<std::string, Milx::Actiont>::iterator iter = actionsCallbacks.find(req.action());
    if (iter != actionsCallbacks.end())
        return iter->second(req);
    else
        return 0;
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

Milx::Response* Milx::Controller::view_response(std::string view)
{
    Milx::Response* resp = new Milx::Response();
    resp->content(Milx::View::render_file(module().viewsPath() / view));
    
    return resp;
}
