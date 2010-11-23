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

#ifndef MILX_CONTROLLER_H
#define MILX_CONTROLLER_H

#include <string>
#include <tr1/memory>

#include <milx/callback.h>
#include <milx/http/call.h>

#define GET_CLASS_NAME(c)\
  std::string(#c).substr(std::string(#c).rfind(':') + 1)

namespace milx {
  /**
   * Milx::Controller is the base class for any Controller in your application.
   */
  class Controller {
    milx::callback::List _actions;
   public:
    template <typename T>
    register_action(const std::string& str, void (T::*func)(http::Call&)) {
      _actions.add(str, (T*)this, func);
    }
    milx::callback::List& actions() { return _actions; }
  };

  typedef std::tr1::shared_ptr<Controller> ControllerPtr;
}

#endif  // MILX_CONTROLLER_H
