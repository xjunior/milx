#include <milx/routing.h>
#include <iostream>
#include "blog.h"

void routing(Milx::Routing& routes)
{
    routes.controller(new BlogController(), "blog");
}
