#include <string>
#include <boost/bind.hpp>
#include "blog.h"

BlogController::BlogController()
{
    registerAction(boost::bind(&BlogController::index, this, _1), "index");
}

Milx::Response* BlogController::index(Milx::Request* req)
{
    Milx::Response* resp = new Milx::Response();
    resp->setContent("BlogController::index(); via " + req->userAgent());

    return resp;
}

