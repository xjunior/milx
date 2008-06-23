#include <iostream>
#include <typeinfo>
#define _MILX_USE_METHOD FCGI
using namespace std;

class AbstractRequest
{
};

namespace CGI
{
    class Request : public AbstractRequest
    {
    };
}

namespace FCGI
{
    class Request : public AbstractRequest
    {
    };
}

class App
{
    AbstractRequest* request;
    public:
    App()
    {
        request = new _MILX_USE_METHOD::Request();
        cout << "Request type: " << typeid(request).name() << endl;
    }
};

int main()
{
    App cgiapp;
}
