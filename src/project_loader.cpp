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

#include <cstdlib>
#include <iostream>
#include <vector>
#include "project_loader.hpp"
#include "path.hpp"

void Milx::ProjectLoader::validate_existence(const Milx::Path& path)
{
	if (!path.exists()) {
		std::cerr << path.str() << " does not exist." << std::endl;
		exit(1);
	}
}

// TODO: recursive
void Milx::ProjectLoader::load_modules(Milx::Application& app, const Milx::Path& path)
{
	validate_existence(path);

	Milx::Path::List solist = Milx::Path::ls((path / "*.so").str().c_str());
	Milx::Path::List::iterator it;

	for (it = solist.begin(); it != solist.end(); it++) {
		try {
			app.loadModule(*it);
		} catch (const std::exception &ex) { }
	}
}

