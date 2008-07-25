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

#include "debug.h"
#include "controller.h"
#include "request.h"
#include "response.h"

Milx::Response* Milx::Controller::dispatch(Milx::Request *req)
{
    DEBUG("Dispatching " << req->controller() << "#" << req->action());
    DEBUG("We have " << actionsCallbacks.size() << " actions");
    std::map<std::string, Milx::Actiont>::iterator iter = actionsCallbacks.find(req->action());
    if (iter != actionsCallbacks.end())
    {
        DEBUG("Action found: " << iter->first << " => " << typeid(iter->second).name());;
        //return new Milx::Response("deu erro");
	return iter->second(req);
    }
    else
        return 0;
}

void Milx::Controller::registerAction(Milx::Actiont mptr, std::string name)
{
    DEBUG("Adding " << name);
    actionsCallbacks.insert( make_pair(name, mptr) );
}

