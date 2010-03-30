#include "project_loader.hpp"

void Milx::ProjectLoader::validate_existence(const fs::path& path)
{
	if (!fs::exists(path)) {
		std::cerr << path << " does not exist." << std::endl;
		exit(1);
	}
}

void Milx::ProjectLoader::load_modules(Milx::Application& app, const fs::path& path, bool recursive)
{
	validate_existence(path);

	fs::directory_iterator end_iter;

	for (fs::directory_iterator dir_itr(path); dir_itr != end_iter; ++dir_itr) {
		try {
			if (fs::is_regular_file(dir_itr->status()) &&
				dir_itr->path().extension().compare(".so") == 0)
				app.loadModule(dir_itr->path());
			else if (recursive && fs::is_directory(*dir_itr))
				load_modules(app, dir_itr->path());
		} catch (const std::exception & ex) { }
	}
}

