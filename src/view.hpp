#ifndef MILX_VIEW_HPP
#define MILX_VIEW_HPP

#include <boost/filesystem/path.hpp>
#include <map>

namespace Milx
{
    namespace View
    {
        class Base;
        
        static std::map<std::string, Base*> instances;
        std::string render_file(boost::filesystem::path);
    }
}

#endif
