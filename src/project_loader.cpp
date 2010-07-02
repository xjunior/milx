#include <cstdlib>
#include <iostream>
#include <vector>
#include "project_loader.hpp"
#include "path.hpp"

void Milx::ProjectLoader::validate_existence(const Milx::Path& path)
{
	if (!path.exists()) {
		std::cerr << path.path() << " does not exist." << std::endl;
		exit(1);
	}
}

// TODO: recursive
void Milx::ProjectLoader::load_modules(Milx::Application& app, const Milx::Path& path)
{
	validate_existence(path);

	Milx::Path::List solist = Milx::Path::ls((path / "*.so").path().c_str());
	Milx::Path::List::iterator it;

	for (it = solist.begin(); it != solist.end(); it++) {
		try {
			app.loadModule(*it);
		} catch (const std::exception &ex) { }
	}
}

