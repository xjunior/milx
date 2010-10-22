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
 *
 * Based on QDebug from Qt(r)
 */

#ifndef MILX_LOGGER_H
#define MILX_LOGGER_H

#include <string>
#include <iostream>
#include <sstream>

namespace milx {
  class Logger {
    enum Severity { WARN, INFO, ERROR };
    std::ostream& _ostream;
   public:
    class Log {
      std::ostream& _ostream;
      std::stringstream _sstream;
      Severity _severity;
      int _copies;
     public:
      Log(std::ostream&, Severity);
      Log(const Log& l);
      ~Log();

      Log& operator<<(const std::string&);
      Log& operator<<(const int&);

      inline std::stringstream& stream() { return _sstream; }
    };

    Logger(std::ostream& = std::cout);
    inline Log warn() const { return Log(_ostream, WARN); }
    inline Log info() const { return Log(_ostream, INFO); }
    inline Log error() const { return Log(_ostream, ERROR); }

    inline std::ostream& stream() const { return _ostream; }
  };
}

#endif  // MILX_LOGGER_H
