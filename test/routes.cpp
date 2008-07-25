#include <milx/routing.h>
#include <iostream>
#include "blog.h"

void routing(Milx::Routing& routes)
{
    std::cout << __FILE__ << ":" << __LINE__ << ": " << "carregando rotas do blog" << std::endl;
    routes.controller(new BlogController(), "blog");
}
