/*
 * Copyright 2010 Carlos Junior
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

#include <dlfcn.h>
#include "shared_module.h"
#include "path.h"

milx::SharedModule::SharedModule(Application& app, const milx::Path &file)
  : milx::Module(app, file.stem()) {
  _shared = dlopen(file.str().c_str(), RTLD_LAZY);
  if (_shared) {
    typedef void(*on_load_f)(milx::Module&);
    on_load_f on_load = (on_load_f) dlsym(_shared, MILX_MODULE_LOAD);

    if (on_load) {
      views_path(file / ".." / "views");
      on_load(*this);
      app.logger().info() << "Load Successfull!";
    } else {
      app.logger().error() << MILX_MODULE_LOAD
        << "method not found in" << file.str().c_str();
    }
  } else {
    app.logger().error() << "The module could not be loaded:"
        << file.str().c_str();
  }
}

milx::SharedModule::~SharedModule() {
  dlclose(_shared);
}

