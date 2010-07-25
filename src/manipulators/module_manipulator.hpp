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

#ifndef MILX_MODULE_MANIPULATOR
#define MILX_MODULE_MANIPULATOR

#include "base.hpp"

namespace Milx
{
	namespace Manipulators
	{
		class ModuleManipulator : public Base
		{
		public:
			void create(std::string, int, char**);
			void destroy(std::string, int, char**);
			void help(std::string, int, char**);
		};
	}
}

#endif
