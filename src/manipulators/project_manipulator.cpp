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

