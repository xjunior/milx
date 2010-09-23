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
#include "action_callback.h"
#include "http/call.h"
#include "view.h"

#define register_action(c)\
  { std::string a = #c;\
  int b = a.rfind(':');\
  if (b == -1) b = 0;\
  a = a.substr(b + 1, a.size() - b);\
  action(Milx::ActionCallback::make_callback(this, &c), a); }

namespace milx {
  class Module;

  /**
   * Milx::Controller is the base class for any Controller in your application.
   */
  class Controller {
    Module* _module;
    /**
     * The actions of your controller
     */
    std::map<std::string, milx::ActionCallback::CallbackBase*> _actions;
   public:
    /**
     * Register an action in your controller. Mostly of developers use this
     * in the class constructor.
     */
    void action(milx::ActionCallback::CallbackBase*, const std::string&);
    milx::ActionCallback::CallbackBase* action(const std::string& name);

    void module(milx::Module*);
    milx::Module& module();
    milx::view::Renderer* get_view(const std::string&);
  };
}

#endif  // MILX_CONTROLLER_H
