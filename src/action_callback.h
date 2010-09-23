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

#ifndef MILX_ACTION_CALLBACK_HPP
#define MILX_ACTION_CALLBACK_HPP

#define MILX_CALLBACK_FUNCTION(a) void (T::*a)(milx::http::Call&)

namespace milx {
  namespace http { class Call; }
  namespace ActionCallback {
    class CallbackBase {
    public:
      virtual void call(milx::http::Call&)=0;
    };

    template <class T> class Callback : public CallbackBase {
    public:
      Callback(T* obj, MILX_CALLBACK_FUNCTION(func))
        :  _obj(obj), _func(func) {
      }
      virtual void call(milx::http::Call &call) {
        (*_obj.*_func)(call);
      }
    private:
      MILX_CALLBACK_FUNCTION(_func);
      T *_obj;
    };

    template <class T>
    Callback<T>* make_callback(T *obj, MILX_CALLBACK_FUNCTION(func)) {
      return new Callback<T>(obj, func);
    }
  }
}

#endif
