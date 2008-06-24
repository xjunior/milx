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
#include "callback.h"

namespace Milx
{
    class Response;
    class Request;

    /**
     * Milx::Controller is the base class for any Controller in your application.
     */
    class Controller
    {
        /**
         * The actions of your controller
         */
        std::map<std::string, Callback*> actionsCallbacks;
    public:
        /**
         * Register an action in your controller. Mostly of developers use this
         * in the class constructor.
         */
        template<class T>
        void registerAction(Milx::Response* (T::*)(Milx::Request*), std::string, T*);
        /**
         * Dispatch an action given by Milx::Request#action() method.
         */
        Milx::Response* dispatch(Milx::Request*);
    };
}

template<class T>
void Milx::Controller::registerAction(Milx::Response* (T::*mptr)(Milx::Request*), std::string action, T *ptr)
{
    actionsCallbacks[action] = new CallbackHandler<T>(mptr, ptr);
}

#endif
