#include "view.hpp"
#include "view/plain.hpp"

std::string Milx::View::render_file(boost::filesystem::path file)
{
    Milx::View::Base* renderer;
    renderer = Milx::View::instances[file.extension()];

    if (renderer == 0) {
		if (!Milx::View::instances["plain"])
			Milx::View::instances["plain"] = new Milx::View::Plain;
		renderer = Milx::View::instances["plain"];
	}

    return renderer->render_file(file);
}
