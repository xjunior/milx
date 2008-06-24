#ifndef BLOG_H
#define BLOG_H

#include <milx/response.h>
#include <milx/request.h>
#include <milx/controller.h>

class BlogController : public Milx::Controller
{
public:
    BlogController();
    Milx::Response* index(Milx::Request*);
};

#endif
