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

#ifndef MILX_VIEW_H
#define MILX_VIEW_H

#include <map>
#include <string>
#include <tr1/memory>  // FIXME windows uses only memory

#include "path.h"
#include "serialization.h"

namespace milx {
  namespace view {
    class Renderer;

    class FactoryBase {
     public:
      virtual milx::view::Renderer* create_view(const milx::Path&)=0;
    };
    template <typename T>
    class Factory : public FactoryBase {
     public:
      milx::view::Renderer* create_view(const milx::Path& p) const {
        return new T(p);
      }
    };

    extern std::map<std::string, std::tr1::shared_ptr<FactoryBase> > instances;

    template <typename T> void register_handler(const std::string& n) {
      instances[n] = new Factory<T>();
    }
    milx::view::Renderer* create_view(const milx::Path&);
  }
}

#endif  // MILX_VIEW_H
