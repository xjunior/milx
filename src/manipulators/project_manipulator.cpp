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
#include "project_manipulator.hpp"

void Milx::Manipulators::ProjectManipulator::create(std::string name, int argc, char* argv[])
{
	std::cout << "Creating " << name << std::endl;

    boost::filesystem::path project(name);

    create_dir(project);
	create_project_cmake(project);
    create_dir(project / "modules");
    create_dir(project / "public");
    create_dir(project / "public" / "img");
    create_dir(project / "public" / "css");
    create_dir(project / "public" / "js");
    //create_file(project / "public" / ".htaccess", public_htaccess);
    create_dir(project / "src");
    create_dir(project / "plugins");
    create_dir(project / "tmp");
}

void Milx::Manipulators::ProjectManipulator::destroy(std::string name, int argc, char* argv[])
{
	std::cout << "Destroying " << name << std::endl;
	boost::filesystem::remove_all(name);
}

void Milx::Manipulators::ProjectManipulator::help(std::string verb, int argc, char* argv[])
{
	std::cout << "\tcreate project [project-name]" << std::endl;
	std::cout << "\tThe project name will also be the name of the directory that your project will be placed in." << std::endl;
}

void Milx::Manipulators::ProjectManipulator::create_project_cmake(boost::filesystem::path path)
{
    append_file(path / "CMakeLists.txt", "", false);
}

