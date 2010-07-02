#include "path.hpp"
#include <unistd.h>
#include <cstdlib>
#include <cstdarg>
#include <sstream>
#include <magic.h>
#include <glob.h>

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

Milx::Path::Path() : _path("")
{
}

Milx::Path::Path(std::string path)
{
	const char * cpath = canonicalize_file_name(path.c_str());
	_path = (cpath == NULL) ? path : cpath;
	// TODO checkout realpath

	_stat = new Milx::Path::Stat(*this);

	delete cpath;
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

// TODO css and js are being badly detected, I must find a better way for this
std::string Milx::Path::type() const
{
	magic_t cookie;
	std::string type;
	cookie = magic_open(MAGIC_MIME);
	if (cookie != NULL) {
		magic_load(cookie, NULL);
		type = magic_file(cookie, _path.c_str());
	}
	magic_close(cookie);
	return type;
}

const Milx::Path::Stat& Milx::Path::stat() const
{
	return *_stat;
}

Milx::Path::Stat::Stat(Milx::Path &path)
{
	::stat(path.path().c_str(), &_stat);
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

int Milx::Path::Stat::size() const
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
