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

#ifndef MILX_CALLBACK_H
#define MILX_CALLBACK_H

#include <string>

namespace Milx
{
    class Request;
    class Response;

    /**
     * The Callback class is an abstract class to help Milx to handle the
     * calling of actions.
     * 
     * This class was made to help Milx to call an action by it's string name.
     */
    class Callback
    {
    public:
        /**
         * Call an the action passing the Milx::Request, and expect a
         * Milx::Response as it's return.
         */
        virtual Milx::Response* call(Milx::Request*)=0;
    };

    /**
     * CallbackHandler can handle callbacks for any Controller class. It's
     * a template class
     */
    template<class T>
    class CallbackHandler : public Callback
    {
        /**
         * Pointer to the action method being held.
         */
        Milx::Response* (T::*method)(Milx::Request*);
        /**
         * Pointer to the object being held.
         */
        T *obj;
    public:
        /**
         * CallbackHandler constructor.
         * \param mptr is the pointer to the action
         * \param optr is the pointer to the controller
         */
        CallbackHandler(Milx::Response* (T::*)(Milx::Request*), T*);
        /**
         * Call the action, passing a request and expecting a response
         * \param req is the current request
         * \return a http response
         */
        Milx::Response* call(Milx::Request*);
    };
}
template<class T>
Milx::CallbackHandler<T>::CallbackHandler(Milx::Response* (T::*mptr)(Milx::Request*), T* optr) : obj(optr), method(mptr) { }

template<class T>
Milx::Response* Milx::CallbackHandler<T>::call(Milx::Request *req)
{
    return (obj->*method)(req);
}
#endif
