#ifndef MILX_PROJECT_LOADER_HPP
#define MILX_PROJECT_LOADER_HPP

#include "application.hpp"

#define MILX_PROJECT_MODULES_DEFAULT "modules"

namespace Milx
{
	class Path;
	class ProjectLoader
	{
		static void validate_existence(const Milx::Path& path);
	public:
		static void load_modules(Application&, const Milx::Path&);
		static void load(Application& app, const Milx::Path& path)
		{
			load_modules(app, path / MILX_PROJECT_MODULES_DEFAULT);
		}
	};
}

#endif
