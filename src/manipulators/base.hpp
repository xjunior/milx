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

#ifndef MILX_MANIPULATOR_BASE
#define MILX_MANIPULATOR_BASE

#include <string>
#include <map>
#include <boost/filesystem.hpp>

namespace Milx
{
	namespace Manipulators
	{
		class Base
		{
		public:
			virtual void create(std::string, int, char**)=0;
			virtual void destroy(std::string, int, char**)=0;
			virtual void help(std::string, int, char**)=0;
			void display_help(std::string, int, char**);
		protected:
			void create_dir(boost::filesystem::path);
			void append_file(boost::filesystem::path, std::string, bool=true);
		private:
			bool create_info(boost::filesystem::path);
		};
	}
}

#endif
