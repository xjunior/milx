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

    class Callback
    {
    public:
        virtual Milx::Response* call(Milx::Request*)=0;
    };

    template<class T>
    class CallbackHandler : public Callback
    {
        Milx::Response* (T::*method)(Milx::Request*);
        T *obj;
    public:
        CallbackHandler(Milx::Response* (T::*)(Milx::Request*), T*);
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
