#ifndef BLOG_H
#define BLOG_H

#include "response.h"
#include "request.h"
#include "controller.h"

class BlogController : public Milx::Controller
{
public:
    BlogController();
    Milx::Response* index(Milx::Request*);
};

#endif
