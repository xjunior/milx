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

#include <list>
#include <string>
#include <tr1/memory>
#include <map>

#include <milx/path.h>

namespace milx {
  namespace view {
    class BoundValue {
      std::string _name;
      std::string _value;

      std::list<BoundValue*> _children;
     public:
      explicit BoundValue(const std::string& name) : _name(name) { }
      std::string name() const { return _name; }
      std::string value() const { return _value; }
      const std::list<BoundValue*>& children() const { return _children; }

      template <typename InputIterator>
      BoundValue& push(InputIterator begin, InputIterator end,
              std::string col_name, std::string sig_name = "") {
        if (sig_name.size() == 0) {
          sig_name = col_name;
          col_name = sig_name + "S";
        }

        BoundValue *node = new BoundValue(col_name);
        for (; begin != end; ++begin) node->push(sig_name) << **begin;
        _children.push_back(node);

        return *node;
      }

      /*template <typename ValueType>
      BoundValue& push(const std::map<std::string, ValueType> &map,
              std::string col_name) {
        std::map<std::string, ValueType>::const_iterator itr;

        BoundValue *node = new BoundValue(col_name);
        for (itr = map.begin(); itr != map.end(); ++itr) {
          node->push((*itr).first) << (*itr).second;
        }
        _children.push_back(node);

        return *node;
      }*/

      BoundValue& push(const std::string& name);
      BoundValue& operator<<(const std::string& str);
      BoundValue& operator<<(const int& num);
    };

    class Renderer {
     public:
      virtual bool accept(const std::string& mime) = 0;
      virtual void render(milx::Path &path, BoundValue &bnd,
                                  std::ostream &out) = 0;
      /*virtual std::string render(const std::string &str, BoundValue &bnd,
                                  std::stream &out) = 0;*/
    };

    extern struct _renderers {
      std::list<std::tr1::shared_ptr<Renderer> > list;

      template <typename T> void add() {
        list.push_front(std::tr1::shared_ptr<Renderer>(new T));
      }

      std::tr1::shared_ptr<Renderer> get(const std::string &mime) {
        std::list<std::tr1::shared_ptr<Renderer> >::iterator begin;
        for (begin = list.begin(); begin != list.end(); ++begin) {
          if ((*begin)->accept(mime))
            return *begin;
        }
        // TODO(xjunior) throw exception
      }
    } renderers;

    class Base {
      view::BoundValue _bound;
     public:
      Base() : _bound("context") { }

      BoundValue& bound() { return _bound; }
      void bound(const view::BoundValue& bound) { _bound = bound; }

      virtual std::string mime_output() = 0;
      virtual void render(std::ostream &out) = 0;
    };

    class File : public Base {
      milx::Path _path;
     public:
      File(const milx::Path& p) : _path(p), Base() { }

      virtual std::string mime_output();
      virtual void render(std::ostream &out);
    };
  }
}

#endif  // MILX_VIEW_H
