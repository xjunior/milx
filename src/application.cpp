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
#include <iostream>
#include "application.hpp"
#include "response.hpp"
#include "request.hpp"
#include "controller.hpp"
#include "logger.hpp"

Milx::Application::Application()
{
    this->logger(new Milx::Logger(std::cout));
}

void Milx::Application::controller(Milx::Controller* c, std::string name)
{
    this->_controllers[name] = c;
}

Milx::Controller* Milx::Application::controller(std::string name)
{
    return this->_controllers[name];
}

void Milx::Application::loadFile(const boost::filesystem::path file)
{
    this->logger()->info("Loading " + file.file_string());

    void* opened = dlopen(file.file_string().c_str(), RTLD_LAZY);
    if (opened)
    {
        _loaded.push_back(opened);
    
        typedef void(*on_load_f)(Milx::Application&);
        on_load_f on_load = (on_load_f) dlsym(opened, "milx_on_load");

        if (on_load)
            on_load(*this);
        else
            this->logger()->error("milx_on_load method not found in " + file.file_string());
    }
    else
        this->logger()->error("The module could not be loaded: " + file.file_string());
}

Milx::Response* Milx::Application::dispatch(Milx::Request& req)
{
    this->logger()->info("Attending request to " + req.fullPath());
    if (!routes.translateRequest(req))
    {
        this->logger()->warn("No route found, returning 404");
    	return new Milx::Response("File not found.", 404);
    }
    
    Milx::Controller* controller = this->controller(req.controller());
    
    if (controller == NULL)
    {
        this->logger()->warn("Route error: Bad controller name: " + req.controller());
    	return new Milx::Response("Bad controller name.", 500);
    }
    
    this->logger()->info("Routed to " + req.controller() + "/" + req.action());
    Milx::Response *response = controller->dispatch(req);
    //this->logger()->info("Elapsed " + time);
    return response;
}

Milx::Application::~Application()
{
    if (_loaded.size() > 0)
        for (register int i = 0; i < _loaded.size(); i++)
	    dlclose(_loaded[i]);
}
