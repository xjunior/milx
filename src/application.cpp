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

#include <dlfcn.h>
#include "application.h"
#include "response.h"
#include "request.h"
#include "controller.h"

Milx::Application::Application()
{ }

void Milx::Application::loadFile(std::string filename)
{
    register int pos = loaded.size();
    loaded.push_back(dlopen(filename.c_str(), RTLD_LAZY));
    if (!loaded[pos]) throw LoaderNotFound();
    
    typedef void(*on_load_f)(Milx::Application&);
    on_load_f on_load = (on_load_f) dlsym(loaded[pos], "on_load");

    if (on_load)
        on_load(*this);
    else
        throw LoaderNotFound();
}

Milx::Response* Milx::Application::dispatch(Milx::Request* req)
{
    Milx::Controller* controller = routes.translateRequest(req);
    // TODO: create a Milx::InternalErrorResponse
    return controller->dispatch(req);
}

Milx::Application::~Application()
{
    if (loaded.size() > 0)
        for (register int i = 0; i < loaded.size(); i++)
	    dlclose(loaded[i]);
}

