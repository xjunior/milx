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

#include "application.h"
#include "controller.h"
#include "response.h"

class Blog : public Milx::Controller
{
    Milx::CGI::Response index();
public:
    Milx::CGI::Response callAction(std::string name);
};

Milx::CGI::Response Blog::index()
{
    return Milx::CGI::Response( "<html>"
    "<head><title>Milx Blog System</title></head>"
    "<body>"
    "<h1>Milx Blog System</h1>"
    "<p>You're using: <b>" +request().userAgent() + "</b></p>"
    "</body></html>" );
}

Milx::CGI::Response Blog::callAction(std::string name)
{
    if (name.compare("index") == 0) return index();
}

int main()
{
    Milx::Application a("blog");
    a.registerController(new Blog());
    return a.run();
}

