#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <string>
#include <iostream>
using namespace boost::filesystem;

void usage(int=0);
void create_project(std::string);
void create_dir(path);
void create_file(path, std::string);
bool creation_info(path);

const std::string htaccess = "# General Apache options\n"
"RewriteEngine On\n"
"RewriteRule    ^$ public/    [L]\n"
"RewriteRule    (.*) public/$1 [L]";

const std::string public_htaccess = "# General Apache options\n"
"AddHandler cgi-script .cgi\n"
"Options +FollowSymLinks +ExecCGI\n"
"RewriteEngine On\n"
"RewriteRule ^$ index.html [QSA]\n"
"RewriteRule ^([^.]+)$ $1.html [QSA]\n"
"RewriteCond %{REQUEST_FILENAME} !-f\n"
"RewriteRule ^(.*)$ milx.cgi [QSA,L]\n"
"ErrorDocument 500 \"<h1>Milx Application Error</h1><p>Milx Application failed to start properly</p>\"";

int main(int argc, char* argv[])
{
    if (argc == 2)
    {
        if (std::string(argv[1]).compare("--help") == 0)
            usage();
        else
            create_project(argv[1]);
    }
    else
        usage(1);
}

void usage(int code)
{
    std::cout << "Milx Web Application Framework" << std::endl;
    std::cout << "milx missing operand" << std::endl;
    std::cout << "Please, provide the project name. Usage: milx project_name" << std::endl;
    exit(code);
}

void create_project(std::string name)
{
    path project(name);
    create_dir(project);
    create_file(project / ".htaccess", htaccess);
    create_dir(project / "build");
    create_dir(project / "public");
    create_dir(project / "public" / "img");
    create_dir(project / "public" / "css");
    create_dir(project / "public" / "js");
    create_file(project / "public" / ".htaccess", public_htaccess);
    create_dir(project / "src");
}

void create_dir(path dir)
{
    if (!creation_info(dir))
        create_directory(dir);
}

void create_file(path path, std::string content)
{
    if (!creation_info(path))
    {
        ofstream file(path);
        file << content;
        file.close();
    }
}

bool creation_info(path path)
{
    bool exist = exists(path);
    std::cout << "\t" << (exist ? "exists" : "create");
    std::cout << " " << path << std::endl;

    return exist;
}

