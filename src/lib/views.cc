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

#include <fstream>
#include <string>
#include <tr1/memory>
#include <iostream>

#include <cstdio>

#include <milx/views.h>

milx::view::_renderers milx::view::renderers;

milx::view::BoundValue& milx::view::BoundValue::push(const std::string& name) {
  milx::view::BoundValue *node = new milx::view::BoundValue(name);
  _children.push_back(node);

  return *node;
}

milx::view::BoundValue& milx::view::BoundValue::operator<<(const std::string& t) {
  _value.append(t);
  return *this;
}

milx::view::BoundValue& milx::view::BoundValue::operator<<(const int& t) {
  char buff[6];
  sprintf(buff, "%d", t);
  _value.append(buff);
  return *this;
}

milx::view::Template::Template(const std::string& o_t, const std::string& i_t)
  : _bound("context"), _output_type(o_t), _input_type(i_t) {
}

milx::view::Template::Template(const milx::Path& p)
  : _bound("context") {
  load_file(p);
}

void milx::view::Template::load_file(const milx::Path& p) {
  _input_type = p.type();
  _output_type = milx::Path(p.stem()).type();

  std::ifstream in(p.str().c_str(), std::ios::in);
  while (!in.eof())
    _template.push_back(in.get());

  in.close();
}

void milx::view::Template::render(std::ostream &out) {
  std::tr1::shared_ptr<milx::view::Renderer> renderer =
    milx::view::renderers.get(_input_type);
  renderer->render(_template, bound(), out);
  // TODO(xjunior) catch renderers.get thrown exception
}
