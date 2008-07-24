#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

bool is_so(char f[], char ext[])
{
    char *res = strstr(f, ext);
    return res && strcmp(res, ext) == 0;
}

int getdir (string dir)
{
    DIR *dp;
    struct dirent *dirp;
    if ((dp  = opendir(dir.c_str())) == NULL)
    {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL)
    {
        cout << dirp->d_name << ": " << endl;
        cout << (is_so(dirp->d_name, ".so") ? "sim" : "não");
    }
 
    closedir(dp);
    return 0;
}

int main()
{
    getdir(".");
    return 0;
}

