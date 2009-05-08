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
#include "application.hpp"
#include "response.hpp"
#include "request.hpp"
#include "controller.hpp"
#include "logger.hpp"
#include "shared_module.hpp"

Milx::Application::Application()
    : Milx::Module()
{
    this->logger(new Milx::Logger(std::cout));
}

void Milx::Application::loadFile(const boost::filesystem::path file)
{
    this->logger()->info("Loading " + file.file_string());
    _modules.push_back(new Milx::SharedModule(*this, file));
}

Milx::Response* Milx::Application::dispatch(Milx::Request& req)
{
    this->logger()->info("Attending request to " + req.fullPath());

    this->routes().translateRequest(req); // try default module as highest priority
    Milx::Controller* controller = this->controller(req.controller());
    
    for (int i = 0; i < _modules.size() && controller == NULL; i++)
        if (_modules[i]->routes().translateRequest(req))
            controller = _modules[i]->controller(req.controller());
            // it found a route, but if controller STILL NULL, so we try another one

    if (controller == NULL)
    {
        if (req.controller() == "")
        {
            this->logger()->warn("No route found, returning 404");
    	    return new Milx::Response("File not found.", 404);
        }
        else
        {
            this->logger()->warn("Route error: Bad controller name: " + req.controller());
            return new Milx::Response("Bad controller name.", 500);
        }
    }
    else
    {
        this->logger()->info("Routed to " + req.controller() + "/" + req.action());
        return controller->dispatch(req);
    }
}

Milx::Application::~Application()
{
    if (_modules.size() > 0)
        for (register int i = 0; i < _modules.size(); i++)
            delete _modules[i];
}

void Milx::Application::logger(Milx::Logger* logger)
{
    if (logger != NULL)
        _logger = logger;
}

