#ifndef MILX_VIEW_RENDERER_HPP
#define MILX_VIEW_RENDERER_HPP

#include <map>
#include <string>

namespace Milx
{
	class Path;
	namespace View
	{
		namespace Renderer
		{
			class Base;

			static std::map<std::string, Base*> instances;
			std::string render_file(const Milx::Path&);
		}
    }
}

#endif
