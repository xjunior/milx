#include "blog.h"

BlogController::BlogController()
{
    registerAction(&BlogController::index, "index", this);
}

Milx::Response* BlogController::index(Milx::Request* req)
{
    Milx::Response* resp = new Milx::Response();
    resp->setContent("BlogController::index(); via " + req->userAgent());

    return resp;
}

