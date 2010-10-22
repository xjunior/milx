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
#include <map>
#include <memory>

#include <milx/action_callback.h>
#include <milx/http/call.h>

#define GET_CLASS_NAME(c)\
  std::string(#c).substr(std::string(#c).rfind(':') + 1)

#define register_action(c)\
  action(milx::ActionCallback::make_callback(this, &c), GET_CLASS_NAME(c));

namespace milx {
  /**
   * Milx::Controller is the base class for any Controller in your application.
   */
  class Controller {
    /**
     * The actions of your controller
     */
    std::map<std::string, milx::ActionCallback::CallbackBasePtr > _actions;
   public:
    /**
     * Register an action in your controller. Mostly of developers use this
     * in the class constructor.
     */
    void action(milx::ActionCallback::CallbackBasePtr, const std::string&);
    milx::ActionCallback::CallbackBasePtr action(const std::string& name);
  };

  typedef std::tr1::shared_ptr<Controller> ControllerPtr;
}

#endif  // MILX_CONTROLLER_H
