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

#include <milx/callback.h>

namespace milx {
  namespace callback {
    void List::fire(const std::string& name, milx::http::Call& call) {
      if (_callbacks.count(name))
        return (*_callbacks[name])(call);
      throw new InvalidCallback;
    }
    void List::fire_all(milx::http::Call& call) {
      std::map<std::string, Base*>::iterator it;
      for (it = _callbacks.begin(); it != _callbacks.end(); ++it)
	(*it->second)(call);
    }
    void List::remove(const std::string& n) {
      if (_callbacks.count(n)) {
	delete _callbacks[n];
	_callbacks.erase(n);
      }
    }
  }
}

