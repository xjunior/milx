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

#include <milx/http/call.h>

#include <string>
#include <sstream>
#include <map>

#include <milx/path.h>
#include <milx/routing.h>
#include <milx/views.h>
#include <milx/logger.h>

milx::http::Call::Call(milx::http::Method method, std::string path)
  : _method(method), _path(path), _content_type("text/html; charset=utf-8"),
  _status(200), _file_content(NULL) {
  _content.str("");
  _content.flush();
  _content.clear();
}

milx::http::Call::~Call() {
  if (_file_content) delete _file_content;
}

void milx::http::Call::content(const milx::Path& path) {
  if (path.exists() && path.stat().is_file()) {
    content_type(path.type());
    _file_content = new milx::Path(path.str());
  } else {
    content().str("");  // FIXME throw a correct exception
  }
}

void milx::http::Call::content(milx::view::Template * const view) {
  view->render(_content);
  content_type(view->mime_output());
}

const milx::Path * const milx::http::Call::file_content() const {
  return _file_content;
}

milx::Logger::Log& operator<<(milx::Logger::Log& os, const milx::http::Call& call) {
  std::stringstream sstream;
  sstream << call.method() << " " << call.path() << std::endl;
  sstream << "\tController: " << call.controller() << std::endl;
  sstream << "\tAction: " << call.action() << std::endl;
  sstream << "\tParams: " << call.params.size() << std::endl;
  sstream << "\tStatus" << call.status() << std::endl;
  sstream << "\tContent Type: " << call.content_type();
  os << sstream.str();

  return os;
}

milx::view::BoundValue& operator<<(milx::view::BoundValue& bnd, const milx::http::Call& call) {
  bnd.push("method") << call.method();
  bnd.push("path") << call.path();
  bnd.push("controller") << call.controller();
  bnd.push("action") << call.action();
  bnd.push(call.params, "params");

  return bnd;
}

