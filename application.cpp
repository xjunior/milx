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

#include <string>
#include <iostream>
#include "application.h"
#include "response.h"

Milx::Application::Application(std::string name)
{
    this->app_name = name;
}

void Milx::Application::registerController(Milx::Controller *c)
{
    controllers.push_back(c);
    c->setApplication(this);
}

int Milx::Application::run()
{
    Milx::CGI::Response response = controllers[0]->callAction("index");
    std::cout << response.fullResponse();
    return 0;
}
