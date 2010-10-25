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

#ifndef MILX_CALLBACK_H
#define MILX_CALLBACK_H

#include <map>
#include <string>
#include <exception>

namespace milx {
  namespace http { class Call; }
  namespace callback {
    class Base {
     public:
      virtual void operator()(milx::http::Call&)=0;
    };

    template <typename T = Base>
    class MemberCallback : public Base {
     public:
      typedef void (T::*FunctionPtr)(milx::http::Call&);

      MemberCallback(T* obj, FunctionPtr fnc) : _obj(obj), _func(fnc) { }
      void operator()(milx::http::Call& call) {
        return (*_obj.*_func)(call);
      }
     private:
      T* _obj;
      FunctionPtr _func;
    };

    class NonMemberCallback : public Base {
     public:
      typedef void (*FunctionPtr)(milx::http::Call&);

      NonMemberCallback(FunctionPtr fnc) : _func(fnc) { }
      inline void operator()(milx::http::Call& call) {
	return (*_func)(call);
      }
     private:
      FunctionPtr _func;
    };

    class InvalidCallback : public std::exception {
     public:
      inline const char * what() {
	return "Invalid callback";
      }
    };

    class List {
      std::map<std::string, Base*> _callbacks;
     public:
      template <typename T>
      void add(const std::string& n, T* o, void (T::*f)(milx::http::Call&)) {
        _callbacks[n] = new MemberCallback<T>(o, f);
      }
      inline void add(const std::string& n, NonMemberCallback::FunctionPtr f) {
        _callbacks[n] = new NonMemberCallback(f);
      }

      void remove(const std::string& n);
      void fire(const std::string& name, milx::http::Call& call);
      void fire_all(milx::http::Call& call);
    };
  }
}
#endif // MILX_CALLBACK_H
