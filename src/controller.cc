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

#include <map>
#include <string>

#include <milx/controller.h>
#include <milx/views.h>
#include <milx/action_callback.h>

milx::ActionCallback::CallbackBasePtr milx::Controller::action(
  const std::string& name) {
  std::map<std::string, milx::ActionCallback::CallbackBasePtr >::iterator iter =
    _actions.find(name);
  if (iter != _actions.end())
    return iter->second;
  else
    ; // TODO(xjunior) throw an error
}

void milx::Controller::action(milx::ActionCallback::CallbackBasePtr mptr,
  const std::string& name) {
  _actions.insert(make_pair(name, mptr));
}

