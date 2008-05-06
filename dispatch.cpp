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

#include "application.h"
#include "controller.h"
#include "response.h"

class Blog : public Milx::Controller
{
    Milx::Response index();
public:
    Milx::Response callAction(std::string name);
};

Milx::Response Blog::index()
{
    return Milx::Response( "<html>"
                "<head><title>Milx Blog Example</title></head>"
                "<body>"
                "<h1> Hello, World! </h1>"
                "</body></html>", 404 );
}

Milx::Response Blog::callAction(std::string name)
{
    if (name.compare("index") == 0) return index();
}

int main()
{
    Milx::Application a("blog");
    a.registerController(new Blog());
    return a.run();
}

