#include <milx/routing.h>
#include "blog.h"

void routing(Milx::Routing& routes)
{
    routes.controller(new BlogController(), "blog");
}
