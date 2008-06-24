#include "cgi_handler.h"
#include "../application.h"

int main(int, char**)
{
    Milx::Application app;
    Milx::CGI::Handler::run(&app);

    return 0;
}
