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

#ifndef MILX_VIEW_PLAIN_H
#define MILX_VIEW_PLAIN_H

#include <string>
#include <boost/filesystem/path.hpp>
#include "base.hpp"

namespace Milx
{
	namespace View
	{
		class Plain : public Base
		{
		public:
			std::string render_file(boost::filesystem::path);
			std::string render_inline(std::string);
		};
	}
}

#endif
