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

#include <cstdlib>
#include <cstdio>
#include <string>
#include <set>

#include "serialization.h"

namespace milx {
  namespace Serialization {
    Node::Node(const std::string& n) : _name(n) {
    }

    Node& Node::push(const std::string& name) {
      NodePtr n = NodePtr(new Node(name));
      _children.insert(n);

      return *n.get();
    }

    Node& Node::operator<<(Serializable* t) {
      t->serialize(*this);
      return *this;
    }

    Node& Node::operator<<(const std::string& t) {
      _value.append(t);
      return *this;
    }

    Node& Node::operator<<(const int& t) {
      char * buff;
      sprintf(buff, "%d", t);
      _value.append(buff);
      return *this;
    }

    Node& Node::operator<<(const List& list) {
      List::const_iterator it;
      for (it = list.begin(); it != list.end(); it++)
        push(_name) << *it;

      if (_name.at(_name.size()-1) != 'S')
        _name.append("S");
    }

    void Serializer::serialize(const Node& n) {
      begin(n._name, n._value);
      std::set<NodePtr>::const_iterator it;
      for (it = n._children.begin(); it != n._children.end(); it++)
        serialize(**it);
      end();
    }

    void YAMLSerializer::begin(const std::string& n, const std::string& v) {
      for (int i = 0; i < _level; i++) _out << "\t";
      _out << n << ": " << v << std::endl;
      _level++;
    }

    void YAMLSerializer::end() {
      _level--;
    }

    void XMLSerializer::begin(const std::string& n, const std::string& v) {
      xmlNodePtr node = xmlNewDocNode(_doc, NULL, BAD_CAST n.c_str(),
                                      BAD_CAST v.c_str());
      if (!_node_stack.empty())
        xmlAddChild(_node_stack.top(), node);

      _node_stack.push(node);
    }

    void XMLSerializer::end() {
      if (_node_stack.size() == 1)
        xmlDocSetRootElement(_doc, _node_stack.top());

      _node_stack.pop();
    }
  }
}
