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

#include <libxml/tree.h>
#include <libxml/xmlsave.h>

#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <stack>

#ifndef MILX_SERIALIZATION_H
#define MILX_SERIALIZATION_H

namespace milx {
  namespace Serialization {
    class Node;
    class Serializer {
      virtual void begin(const std::string&, const std::string&)=0;
      virtual void end()=0;
     public:
      void serialize(const Node&);
    };

    class Serializable {
     public:
      virtual void serialize(Node&) const = 0;
    };
    typedef std::set<Serializable*> List;

    class Node {
      friend class Serializer;
      std::string _name;
      std::string _value;

      std::set<Node*> _children;
      Node(const Node& n) { }
     public:
      explicit Node(const std::string&);

      Node& push(const std::string&);
      Node& operator<<(const std::string& str);
      Node& operator<<(const int& num);
      Node& operator<<(Serializable* ser);
      Node& operator<<(const List& list);
    };

    class YAMLSerializer : public Serializer {
      std::ostream& _out;
      int _level;
     public:
      YAMLSerializer(std::ostream& out) : _out(out) {}

      void begin(const std::string&, const std::string&);
      void end();
    };

    class XMLSerializer : public Serializer {
      xmlDocPtr _doc;
      std::stack<xmlNodePtr> _node_stack;
     public:
      XMLSerializer(xmlDocPtr doc) : _doc(doc) {}

      void begin(const std::string&, const std::string&);
      void end();
    };
  }
}

#endif  // MILX_SERIALIZATION_H
