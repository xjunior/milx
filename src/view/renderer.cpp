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

#include "renderer.hpp"
#include "renderer/plain.hpp"

// TODO: invert file.html.plain to file.plain.html
// this would make the file more 'recognizeable' by users and programs
std::string Milx::View::Renderer::render_file(const Milx::Path &file)
{
	Milx::View::Renderer::Base* renderer;
	renderer = Milx::View::Renderer::instances[file.extension()];

	if (renderer == 0) {
		if (!Milx::View::Renderer::instances["plain"])
			Milx::View::Renderer::instances["plain"] = new Milx::View::Renderer::Plain;
		renderer = Milx::View::Renderer::instances["plain"];
	}

	return renderer->render_file(file);
}

