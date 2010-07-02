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

#ifndef MILX_CONTROLLER_H
#define MILX_CONTROLLER_H

#include <string>
#include <map>
#include "action_callback.hpp"
#include "web_call.hpp"

#define register_action(c)\
	{ std::string a = #c;\
	int b = a.rfind(':');\
	if (b == -1) b = 0;\
	a = a.substr(b + 1, a.size() - b);\
	action(Milx::ActionCallback::make_callback(this, &c), a); }

namespace Milx
{
	class Module;

	/**
	 * Milx::Controller is the base class for any Controller in your application.
	 */
	class Controller
	{
		Module* _module;
		/**
		 * The actions of your controller
		 */
		std::map<std::string, Milx::ActionCallback::CallbackBase*> _actions;
	public:
		/**
		 * Register an action in your controller. Mostly of developers use this
		 * in the class constructor.
		 */
		void action(Milx::ActionCallback::CallbackBase*, std::string);
		Milx::ActionCallback::CallbackBase* action(std::string name);

		void module(Milx::Module*);
		Milx::Module& module();
		// Milx::Response* view_response(std::string);
	};
}

#endif
