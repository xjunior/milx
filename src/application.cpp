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
#include <dlfcn.h>
#include "application.h"
#include "response.h"
#include "request.h"
#include "controller.h"

Milx::Application::Application()
{
    loadRoutes();
}

void Milx::Application::loadRoutes()
{
    void* loader = dlopen("./routes.so", RTLD_LAZY);
    if (!loader) throw RoutesNotFound();
    
    typedef void(*routing_f)(Milx::Routing&);
    routing_f routing = (routing_f) dlsym(loader, "routing");

    if (routing)
    {
        DEBUG("to carregando tudo!!!");
        routing(routes);
        dlclose(loader);
        return;
    }
    else
    {
        throw RoutesNotFound();
        dlclose(loader);
    }
}

Milx::Response* Milx::Application::dispatch(Milx::Request* req)
{
    Milx::Controller* controller = routes.translateRequest(req);
    DEBUG("Going to dispatch " << req->controller() << "#" << req->action());
    // TODO: throw some kind of error if the controller don't exists
    return controller->dispatch(req);
}

