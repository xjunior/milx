#include <iostream>
#include <sstream>
#include <string.h>
#include "manipulators.hpp"
#include "manipulators/project_manipulator.hpp"
#include "manipulators/module_manipulator.hpp"

// TODO: create a separate Shared Object for each Manipulator

void show_usage(std::string="");

int main(int argc, char* argv[])
{
	Milx::Manipulators::instances["project"] = new Milx::Manipulators::ProjectManipulator;
	Milx::Manipulators::instances["module"] = new Milx::Manipulators::ModuleManipulator;

	if (argc == 1 || (argc == 2 && strcmp(argv[1], "help") == 0))
		show_usage("Invalid Syntax");
	else if (argc > 3) {
		Milx::Manipulators::Base* manipulator = Milx::Manipulators::instances[argv[2]];
		if (manipulator) {
			if (strcmp(argv[1], "create") == 0)
				manipulator->create(argv[3], argc, argv);
		    else if (strcmp(argv[1], "destroy") == 0)
				manipulator->destroy(argv[3], argc, argv);
		    else if (strcmp(argv[1], "help") == 0) {
				manipulator->display_help(argv[3], argc, argv);
			} else
				show_usage("Invalid verb");
		} else show_usage("Invalid manipulator");
	} else show_usage("Invalid syntax");
}

inline std::string manipulators_names()
{
	std::stringstream ss;
	std::map<std::string, Milx::Manipulators::Base*>::iterator it;
	for (it = Milx::Manipulators::instances.begin(); it != Milx::Manipulators::instances.end(); it++)
		ss << it->first << " ";
	return ss.str();
}

void show_usage(std::string error)
{
	std::cout << std::endl << "Milx manipulation utility" << std::endl << std::endl;
	if (error.size() > 0) std::cout << "" << error << std::endl << std::endl;
	std::cout << "milx <verb> <manipulator> [params]" << std::endl << std::endl;
	std::cout << "Verbs: create, destroy, help" << std::endl;
	std::cout << "Manipulators: " << manipulators_names() << std::endl;
	std::cout << std::endl;
}

