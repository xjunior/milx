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

#ifndef MILX_VIEW_RENDERER_H
#define MILX_VIEW_RENDERER_H

#include <map>
#include <string>

#include "../path.h"
#include "../serialization.h"

namespace milx {
  namespace view {
    class Renderer {
      milx::Path _path;
      milx::Serialization::Node _context;
     public:
      Renderer(const milx::Path& p, const std::string& cname="c")
        : _path(p), _context(cname) { }

      std::string render();  // convenience method
      virtual void render(std::ostream&)=0;

      milx::Path path() const { return _path; }
      milx::Serialization::Node& context() { return _context; }
    };
  }
}

#endif  // MILX_VIEW_RENDERER_H
