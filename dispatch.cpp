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

#include <iostream>
#include "application.h"
#include "controller.h"

class Blog : public Milx::Controller
{
    void index();
public:
    void callAction(std::string name);
};

void Blog::index()
{
    std::cout << "Content-Type: text/html; charset=UTF-8" << std::endl << std::endl;
    std::cout << "<html>" << std::endl;
    std::cout << "<head><title>Milx Blog Example</title></head>" << std::endl;
    std::cout << "<body>" << std::endl;
    std::cout << "<h1> Hello, World! </h1>" << std::endl;
    std::cout << "</body></html>" << std::endl;
}

void Blog::callAction(std::string name)
{
    if (name.compare("index") == 0) index();
}

int main()
{
    Milx::Application a("blog");
    a.registerController(new Blog());
    return a.run();
}

