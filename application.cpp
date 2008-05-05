/*
 * This file is part of Milx.
 *
 * Milx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Milx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Milx.  If not, see <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

#include <string>
#include <iostream>
#include "application.h"
using namespace std;

Milx::Application::Application(std::string name)
{
    this->app_name = name;
    splitEnvVars();
}

void Milx::Application::splitEnvVars()
{
    string cur, script_name, method, remote_addr;

    script_name = getenv("SCRIPT_NAME");
    method = getenv("REQUEST_METHOD");
    remote_addr = getenv("REMOTE_ADDR");
}

void Milx::Application::registerController(Milx::Controller *c)
{
    controllers.push_back(c);
    c->setApplication(this);
}

int Milx::Application::run()
{
    controllers[0]->callAction("index");
    return 0;
}
