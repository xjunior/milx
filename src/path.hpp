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

#ifndef MILX_PATH_H
#define MILX_PATH_H

#include <string>
#include <map>
#include <list>
#include <sys/stat.h>
#include <magic.h>

// TODO: cross os compatibility
#define MILX_PATH_SEPARATOR "/"

namespace Milx
{
    class Path
    {
    public:
        typedef std::list<Path> List;
        class Stat
        {
            struct stat _stat;
            public:
            Stat(Path&);
            bool is_dir() const;
            bool is_file() const;
            bool is_symlimk() const;
            off_t size() const;
            int uid() const;
            int gid() const;
        };
    private:
		struct __type_map
		{
			std::string mime;
			std::list<std::string> extensions;
		};

        std::string _path;
        Stat *_stat;
		static magic_t _magic;
		static std::list<__type_map> _type_maps;
		public:
		static void initialize_mime_map(const Milx::Path&);
		static void initialize_mime_magic(const Milx::Path * const=0);
		static std::string join(const char *, ...);
		static List ls(const std::string&);
		static Milx::Path cwd();
		/*		static void copy(std::string, std::string);
		static void rm(std::string);
		static void move(std::string, std::string);
		static bool exists(std::string);*/

		Path(const std::string&);
		bool exists() const;
		std::string extension() const;
		std::string stem() const;
		std::string basename() const;
		std::string dirname() const;
		std::string type() const;
		const std::string& str() const { return _path; }
		Milx::Path operator/(const std::string&) const;
		Milx::Path& operator/=(const std::string&);
		Milx::Path& operator=(const std::string&);
		bool can_read() const;
		bool can_write() const;
		bool can_execute() const;
		const Stat& stat() const;
    };
}

#endif
