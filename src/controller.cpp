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

#include <iostream>
#include <typeinfo>
#include "controller.h"
#include "callback.h"
#include "request.h"

Milx::Response* Milx::Controller::dispatch(Milx::Request *req)
{
    /*std::cout << "Temos " << actionsCallbacks.size() << " actions!" << std::endl;
    std::cout << "Chamando " << req->action() << std::endl;
    std::cout << "e é um: " << typeid(actionsCallbacks[req->action()]).name() << std::endl;*/
    if (actionsCallbacks.count(req->action()) != 0)
        return actionsCallbacks[req->action()]->call(req);
    else
        return 0;
}

