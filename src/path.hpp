#ifndef MILX_PATH_H
#define MILX_PATH_H

#include <string>
#include <map>
#include <list>
#include <sys/stat.h>
#include <magic.h>
#include <vector>

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
            int size() const;
            int uid() const;
            int gid() const;
        };
    private:
	struct __type_map
	{
		std::string mime;
		std::vector<std::string> extensions;
	};

        std::string _path;
        Stat *_stat;
	static magic_t _magic;
	static std::vector<__type_map> _type_maps;
    public:
	static void initialize_mime_map(const Milx::Path&);
	static void initialize_mime_magic(const Milx::Path&);
        static std::string join(const char *, ...);
        static List ls(const std::string&);
        static Milx::Path cwd();
        /*		static void copy(std::string, std::string);
        static void rm(std::string);
        static void move(std::string, std::string);
        static bool exists(std::string);*/

        Path(); // only create the Path object
        Path(const std::string&);
        bool exists() const;
        std::string extension() const;
        std::string stem() const;
        std::string basename() const;
        std::string dirname() const;
        std::string type() const;
        /*std::string encoding();
        std::ostream wopen();
        std::istream ropen();*/
        std::string str() const { return _path; }
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
