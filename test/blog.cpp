#include <string>
#include <boost/bind.hpp>
#include <milx/cookie.h>
#include "blog.h"

#define COOKIE_NAME "test"

BlogController::BlogController()
{
    registerAction(boost::bind(&BlogController::index, this, _1), "index");
}

Milx::Response* BlogController::index(Milx::Request* req)
{
    Milx::Response* resp = new Milx::Response();
    std::string cookieinfo;
    Milx::Cookie *cookie = req->cookies().find(COOKIE_NAME);
    
    if (cookie == NULL)
    {
        cookie = new Milx::Cookie(COOKIE_NAME, "a value");
        resp->setCookie(cookie);
        cookieinfo = "cookie set";
    }
    else
    {
        cookieinfo = "cookie value received with value " + cookie->value() + " changing";
        cookie->value("another value");
        resp->setCookie(cookie);
    }

    resp->setContent("<html><body><h1>BlogController::index();</h1>"
    "<h2>via " + req->userAgent() + "</h2>"
    "<p>Cookies: <b>" + cookieinfo + "</b>:" + cookie->name() + "=" + cookie->value() + "</body></html>");

    return resp;
}

