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

#include "path.h"

#include <string.h>
#include <unistd.h>
#include <glob.h>

#include <climits>
#include <cstdlib>
#include <cstdarg>
#include <sstream>
#include <string>
#include <list>

// Mime types parsing
#include <fstream>
#include <iterator>
#include <algorithm>

magic_t milx::Path:: _magic;
std::list<milx::Path::__type_map> milx::Path::_type_maps;

// FIXME segfaulting
std::string milx::Path::join(const char *a, ...) {
  std::stringstream result;
  result << a;
  const char* next;
  va_list args;
  va_start(args, a);
  next = va_arg(args, const char*);
  while (next != NULL) {
    result << MILX_PATH_SEPARATOR;
    result << next;
    next = va_arg(args, const char*);
  }

  va_end(args);

  return result.str();
}

milx::Path milx::Path::cwd() {
  return milx::Path(getcwd(NULL, 0));
}

milx::Path::List milx::Path::ls(const std::string& gl) {
  milx::Path::List list;

  glob_t globbuf;
  int i;
  globbuf.gl_offs = 0;
  if (glob(gl.c_str(), GLOB_DOOFFS, NULL, &globbuf) == 0) {
    for (i = 0; i < globbuf.gl_pathc; i++) {
      list.push_back(milx::Path(globbuf.gl_pathv[i]));
    }
  }

  return list;
}

std::string milx::Path::absolute(const std::string& p) {
  char *cpath = new char[PATH_MAX + 1];
  std::string result;
  if (realpath(p.c_str(), cpath) != NULL)
    result = cpath;
  else
    result = p;

  delete[] cpath;

  return result;
}

milx::Path::Path(const std::string& path)
  : _path(milx::Path::absolute(path)), _stat(*this) {
}

bool milx::Path::exists() const {
  return !access(_path.c_str(), F_OK);
}

std::string milx::Path::basename() const {
  return _path.substr(_path.rfind(MILX_PATH_SEPARATOR) + 1);
}

bool milx::Path::can_read() const {
  return !access(_path.c_str(), R_OK);
}

bool milx::Path::can_write() const {
  return !access(_path.c_str(), W_OK);
}

bool milx::Path::can_execute() const {
  return !access(_path.c_str(), X_OK);
}

std::string milx::Path::extension() const {
  return _path.substr(_path.rfind('.'));
}

std::string milx::Path::stem() const {
  std::string bn = basename();
  return bn.substr(0, bn.rfind('.'));
}

std::string milx::Path::dirname() const {
  std::string dn = _path.substr(0, _path.rfind(MILX_PATH_SEPARATOR));
  char * cdn = canonicalize_file_name(dn.c_str());
  dn = (cdn == NULL) ? dn : cdn;
  delete cdn;
  return dn;
}

milx::Path milx::Path::operator/(const std::string& p) const {
  std::stringstream npath;
  npath << _path;
  npath << MILX_PATH_SEPARATOR;
  npath << p;
  return milx::Path(npath.str());
}

milx::Path& milx::Path::operator/=(const std::string& p) {
  std::stringstream npath;
  npath << _path;
  npath << MILX_PATH_SEPARATOR;
  npath << p;
  _path = npath.str();
  return *this;
}

milx::Path& milx::Path::operator=(const std::string& p) {
  _path = p;
  return *this;
}

std::string milx::Path::type() const {
  for (std::list<__type_map>::iterator it = _type_maps.begin();
        it != _type_maps.end(); it++) {
    if (std::find(it->extensions.begin(), it->extensions.end(),
                  extension().substr(1)) != it->extensions.end())
      return it->mime;
  }

  // if nothing was found
  if (_magic != NULL)
    return magic_file(_magic, _path.c_str());

  return "text/plain";
}

/*const Milx::Path::Stat& Milx::Path::stat() const
{
  return *_stat;
}*/

milx::Path::Stat::Stat(const milx::Path &path) {
  std::string str = path.str();
  ::stat(str.c_str(), &_stat);
}

bool milx::Path::Stat::is_dir() const {
  return S_ISDIR(_stat.st_mode);
}

bool milx::Path::Stat::is_file() const {
  return S_ISREG(_stat.st_mode);
}

bool milx::Path::Stat::is_symlimk() const {
  return S_ISLNK(_stat.st_mode);
}

off_t milx::Path::Stat::size() const {
  return is_file() ? _stat.st_size : 0;
}

int milx::Path::Stat::uid() const {
  return _stat.st_uid;
}

int milx::Path::Stat::gid() const {
  return _stat.st_gid;
}

void milx::Path::initialize_mime_map(const milx::Path& map) {
  std::ifstream fstream(map.str().c_str());
  std::istream_iterator<std::string> it_end;
  std::string line;

  while (getline(fstream, line)) {
    __type_map map;
    // ignore comment lines
    if (line.size() == 0 || line.at(line.find_first_not_of(" \t")) == '#')
      continue;

    std::istringstream exts(line);
    std::istream_iterator<std::string> it(exts);
    for (bool state = true; it != it_end; ++it) {
      if (state) {
        // first is the mime
        map.mime = *it;
        state = false;
      } else {
        // others are extensions
        map.extensions.push_back(*it);
      }
    }
    if (map.extensions.size() > 0) _type_maps.push_back(map);
  }
}

void milx::Path::initialize_mime_magic(const milx::Path * const path) {
  if (_magic) {
    magic_close(_magic);
    initialize_mime_magic(path);
  } else {
    _magic = magic_open(MAGIC_MIME);
    if (_magic)
    if (magic_load(_magic, path == NULL ? NULL : path->str().c_str()) != 0)
      magic_close(_magic);
  }
}

