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

