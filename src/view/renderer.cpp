#include "renderer.hpp"
#include "renderer/plain.hpp"

// TODO: invert file.html.plain to file.plain.html
// this would make the file more 'recognizeable' by users and programs
std::string Milx::View::Renderer::render_file(boost::filesystem::path file)
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

