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

#include <milx/logger.h>

milx::Logger::Logger(std::ostream &st)
  : _ostream(st)
{ }

milx::Logger::Log::Log(std::ostream& o, Severity sev)
  : _ostream(o), _severity(sev), _copies(0) {
  switch (_severity) {
  case WARN: _sstream << "[WARN]"; break;
  case INFO: _sstream << "[INFO]"; break;
  case ERROR: _sstream << "[ERROR]"; break;
  }
}

milx::Logger::Log::Log(const milx::Logger::Log& l)
  : _ostream(l._ostream), _severity(l._severity), _copies(l._copies+1) {
  _sstream.str(l._sstream.str());
}

milx::Logger::Log::~Log() {
  if (!--_copies) {
    _sstream << std::endl;
    _ostream << _sstream.str();
    _ostream.flush();
  }
}

milx::Logger::Log& milx::Logger::Log::operator<<(const int& t) {
  _sstream << " " << t;
  return *this;
}

milx::Logger::Log& milx::Logger::Log::operator<<(const std::string& t) {
  _sstream << " " << t;

  return *this;
}

