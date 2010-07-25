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
