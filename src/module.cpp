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

#include "module.hpp"
#include "routing.hpp"

Milx::Module::Module(std::string name)
 : _name(name)
{ }

std::string Milx::Module::name()
{
    return _name;
}

void Milx::Module::name(std::string name)
{
    _name = name;
}

boost::filesystem::path Milx::Module::viewsPath()
{
    return _views_path;
}

void Milx::Module::viewsPath(boost::filesystem::path vp)
{
    _views_path = vp;
}

void Milx::Module::controller(Milx::Controller* c, std::string name)
{
	c->module(this);
    this->_controllers[name] = c;
}

Milx::Controller* Milx::Module::controller(std::string name)
{
    return this->_controllers[name];
}

Milx::Routing& Milx::Module::routes()
{
    return _routes;
}
