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

#include <fstream>
#include <sstream>
#include "plain.hpp"

std::string Milx::View::Renderer::Plain::render_file(const Milx::Path &filepath)
{
	std::string plain_content;
	std::ifstream file;
	file.open(filepath.str().c_str(), std::ios::in); // Keep compatibility with std::ifstream, but why?
	std::stringstream ss;
	ss << file.rdbuf();
	file.close();

	return ss.str();
}

std::string Milx::View::Renderer::Plain::render_inline(std::string tmpl)
{
	return tmpl;
}

