#include <iostream>
#include "application.h"
#include "controller.h"
using namespace std;
using namespace Milx;

class Blog : public Controller
{
    void index();
public:
    void callAction(std::string name);
};

void Blog::index()
{
    std::cout << "content-type: text/html\n\n" << endl;
    std::cout << "<html>\n<body>\n" << endl;
    std::cout << "<h1> Hello, World! </h1>\n" << endl;

    printf("</P>\n<H1>Environment Variables</H1>\n<P>\n");
    for (int i = 0; application->env[i]; i++)
        printf("%s<BR>\n", application->env[i]);

    std::cout << "</body>\n</html>\n" << endl;
}

void Blog::callAction(std::string name)
{
    if (name.compare("index") == 0)
        index();
}

int main(int argc, char *argv[], char *envp[])
{
    Application a("blog", envp);
    a.registerController(new Blog());
    return a.run();
}
