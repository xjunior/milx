/*
 * Copyright 2010 Carlos Junior
 *
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

#include "project_loader.h"
#include "path.h"

void milx::ProjectLoader::validate_existence(const milx::Path& path) {
  if (!path.exists()) {
    std::cerr << path.str() << " does not exist." << std::endl;
    exit(1);
  }
}

void milx::ProjectLoader::load_modules(milx::Application& app,
                                       const milx::Path& path) {
  validate_existence(path);

  milx::Path::List solist = milx::Path::ls((path / "*.so").str().c_str());
  milx::Path::List::iterator it;

  for (it = solist.begin(); it != solist.end(); it++) {
    try {
      if ((*it).stat().is_dir())
        load_modules(app, *it);
      else if ((*it).stat().is_file())
        app.load_module(*it);
    } catch(const std::exception &ex) {
      app.logger().error() << ex.what();
    }
  }
}

