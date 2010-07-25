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
#include "module_manipulator.hpp"

void Milx::Manipulators::ModuleManipulator::create(std::string name, int argc, char* argv[])
{
	std::cout << "Creating " << name << std::endl;

	boost::filesystem::path path;
    boost::filesystem::path path_src = path / "src" / name;
    boost::filesystem::path path_view = path / "modules" / "views" / name;

    create_dir(path_src);
    create_dir(path_view);
	append_file(path / "CMakeLists.txt", "\nNew module " + name);
}

void Milx::Manipulators::ModuleManipulator::destroy(std::string name, int argc, char* argv[])
{
    boost::filesystem::path path_src("src");
	path_src = path_src / name;
    boost::filesystem::path path_view("modules");
	path_view = path_view / "views" / name;

	std::cout << "Destroying " << name << std::endl;
	boost::filesystem::remove_all(path_src);
	boost::filesystem::remove_all(path_view);
}

void Milx::Manipulators::ModuleManipulator::help(std::string verb, int argc, char* argv[])
{
	std::cout << "\tcreate project [project-name]" << std::endl;
	std::cout << "\tThe project name will also be the name of the directory that your project will be placed in." << std::endl;
}

