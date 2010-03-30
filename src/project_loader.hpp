#ifndef MILX_PROJECT_LOADER_HPP
#define MILX_PROJECT_LOADER_HPP

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>
#include "application.hpp"

#define MILX_PROJECT_MODULES_DEFAULT "modules"

namespace fs = boost::filesystem;

namespace Milx
{
	class ProjectLoader
	{
		static void validate_existence(const fs::path& path);
	public:
		static void load_modules(Application&, const fs::path&, bool=true);
		static void load(Application& app, const fs::path& path)
		{
			load_modules(app, path / MILX_PROJECT_MODULES_DEFAULT);
		}
	};
}

#endif
