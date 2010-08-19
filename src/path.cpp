/*
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

#include "path.hpp"
#include <string.h>
#include <unistd.h>
#include <climits>
#include <cstdlib>
#include <cstdarg>
#include <sstream>
#include <glob.h>

// Mime types parsing
#include <fstream>
#include <iterator>
#include <algorithm>

magic_t Milx::Path:: _magic;
std::list<Milx::Path::__type_map> Milx::Path::_type_maps;

// FIXME segfaulting
std::string Milx::Path::join(const char *a, ...)
{
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

Milx::Path Milx::Path::cwd()
{
	return Milx::Path(getcwd(NULL, 0));
}

Milx::Path::List Milx::Path::ls(const std::string& gl)
{
	Milx::Path::List list;

	glob_t globbuf;
	int i;
	globbuf.gl_offs = 0;
	if (glob(gl.c_str(), GLOB_DOOFFS, NULL, &globbuf) == 0) {
		for (i=0; i < globbuf.gl_pathc; i++) {
			list.push_back(Milx::Path(globbuf.gl_pathv[i]));
		}
	}

	return list;
}

Milx::Path::Path(const std::string& path)
{
	char *cpath = new char[PATH_MAX + 1];
	if (realpath(path.c_str(), cpath) != NULL)
		_path = cpath;
	else _path = path;

	delete[] cpath;

	_stat = new Milx::Path::Stat(*this);
}

bool Milx::Path::exists() const
{
	return !access(_path.c_str(), F_OK);
}

std::string Milx::Path::basename() const
{
	return _path.substr(_path.rfind(MILX_PATH_SEPARATOR) + 1);
}

bool Milx::Path::can_read() const
{
	return !access(_path.c_str(), R_OK);
}

bool Milx::Path::can_write() const
{
	return !access(_path.c_str(), W_OK);
}

bool Milx::Path::can_execute() const
{
	return !access(_path.c_str(), X_OK);
}

std::string Milx::Path::extension() const
{
	return _path.substr(_path.rfind('.'));
}

std::string Milx::Path::stem() const
{
	std::string bn = basename();
	return bn.substr(0, bn.rfind('.'));
}

std::string Milx::Path::dirname() const
{
	std::string dn = _path.substr(0, _path.rfind(MILX_PATH_SEPARATOR));
	char * cdn = canonicalize_file_name(dn.c_str());
	dn = (cdn == NULL) ? dn : cdn;
	delete cdn;
	return dn;
}

Milx::Path Milx::Path::operator/(const std::string& p) const
{
	std::stringstream npath;
	npath << _path;
	npath << MILX_PATH_SEPARATOR;
	npath << p;
	return Milx::Path(npath.str());
}

Milx::Path& Milx::Path::operator/=(const std::string& p)
{
	std::stringstream npath;
	npath << _path;
	npath << MILX_PATH_SEPARATOR;
	npath << p;
	_path = npath.str();
	return *this;
}

Milx::Path& Milx::Path::operator=(const std::string& p)
{
	_path = p;
	return *this;
}

std::string Milx::Path::type() const
{
	for (std::list<__type_map>::iterator it = _type_maps.begin(); it != _type_maps.end(); it++) {
		if (std::find(it->extensions.begin(), it->extensions.end(), extension().substr(1)) != it->extensions.end())
			return it->mime;
	}
	// if nothing was found
	if (_magic != NULL) // magic was initialized
		return magic_file(_magic, _path.c_str());
	return "text/plain";
}

const Milx::Path::Stat& Milx::Path::stat() const
{
	return *_stat;
}

Milx::Path::~Path()
{
	delete _stat;
}

Milx::Path::Stat::Stat(Milx::Path &path)
{
	::stat(path.str().c_str(), &_stat);
}

bool Milx::Path::Stat::is_dir() const
{
	return S_ISDIR(_stat.st_mode);
}

bool Milx::Path::Stat::is_file() const
{
	return S_ISREG(_stat.st_mode);
}

bool Milx::Path::Stat::is_symlimk() const
{
	return S_ISLNK(_stat.st_mode);
}

off_t Milx::Path::Stat::size() const
{
	return is_file() ? _stat.st_size : 0;
}

int Milx::Path::Stat::uid() const
{
	return _stat.st_uid;
}

int Milx::Path::Stat::gid() const
{
	return _stat.st_gid;
}

void Milx::Path::initialize_mime_map(const Milx::Path& map)
{
	std::ifstream fstream(map.str().c_str());
	std::istream_iterator<std::string> it_end;
	std::string line;

	while (getline(fstream, line)) {
		__type_map map;
		// ignore comment lines
		if (line.size() == 0 || line.at(line.find_first_not_of(" \t")) == '#') continue;

		std::istringstream exts(line);
		std::istream_iterator<std::string> it(exts);
		for (bool state = true; it != it_end; ++it) {
			if (state) { // first is the mime
				map.mime = *it;
				state = false;
			} else // others are extensions
				map.extensions.push_back(*it);
		}
		if (map.extensions.size() > 0) _type_maps.push_back(map);
	}
}

void Milx::Path::initialize_mime_magic(const Milx::Path * const path)
{
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

