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

#ifndef MILX_HTTP_CALL_HPP
#define MILX_HTTP_CALL_HPP

#include <string>
#include <sstream>
#include <map>

#include <milx/http/method.h>
#include <milx/logger.h>

namespace milx {
  class Path;
  namespace view {
    class Template;
    class BoundValue;
  }

  namespace http {
    class Call {
      milx::http::Method _method;
      std::string _path;
      std::stringstream _content;
      std::string _controller;
      std::string _action;
      std::string _content_type;
      int _status;
      Path* _file_content;
     public:
      Call(Method, std::string);
      ~Call();

      const Method& method() const { return _method; }
      const std::string& path() const { return _path; }
      const std::string& controller() const { return _controller; }
      const std::string& action() const { return _action; }
      void controller(std::string c) { _controller = c; }
      void action(std::string a) { _action = a; }

      std::map<std::string, std::string> params;
      std::map<std::string, std::string> header;

      // content
      void content_type(std::string s) { _content_type = s; }
      std::string content_type() const { return _content_type; }
      std::stringstream& content() { return _content; }
      void content(const milx::Path& file);
      void content(milx::view::Template* const view);

      void status(int s) { _status = s; }
      int status() const { return _status; }
      const Path * const file_content() const;
    };
  }
}

milx::Logger::Log& operator<<(milx::Logger::Log& os, const milx::http::Call& call);
milx::view::BoundValue& operator<<(milx::view::BoundValue& bnd, const milx::http::Call& call);

#endif
