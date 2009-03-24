#include <milx/application.h>
#include <milx/routing.h>
#include <iostream>
#include "blog.h"

void on_load(Milx::Application& app)
{
    Milx::Routing *routes = new Milx::Routing();
    routes->controller(new BlogController(), "blog");

    app.addRoutes(routes);
}
