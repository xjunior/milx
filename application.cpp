/*
 * This file is part of CPP On Rails.
 *
 * CPP On Rails is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CPP On Rails is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with CPP On Rails.  If not, see <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

#include "application.h"
using namespace Milx;

Application::Application(std::string name, char *env[])
{
    this->app_name = name;
    this->env = env;
}

void Application::registerController(Controller *c)
{
    controllers.push_back(c);
    c->setApplication(this);
}

int Application::run()
{
    controllers[0]->callAction("index");
    return 0;
}
