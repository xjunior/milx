#ifndef MILX_PATH_H
#define MILX_PATH_H

#include <string>
#include <list>
#include <sys/stat.h>

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
        std::string _path;
        Stat *_stat;
    public:
        static std::string join(const char *, ...);
        static List ls(const std::string&);
        static Milx::Path cwd();
        /*		static void copy(std::string, std::string);
        static void rm(std::string);
        static void move(std::string, std::string);
        static bool exists(std::string);*/

        Path();
        Path(std::string); // only create the File object
        bool exists() const;
        std::string extension() const;
        std::string stem() const;
        std::string basename() const;
        std::string dirname() const;
        std::string type() const;
        /*std::string encoding();
        std::ostream wopen();
        std::istream ropen();*/
        std::string path() const { return _path; }
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
