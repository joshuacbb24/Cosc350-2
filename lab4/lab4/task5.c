#include <stdio.h> 
#include <string.h> 
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>  
#include <sys/stat.h>

void err_sys(char *str)
{
printf ("%s\n",str);
exit (1);
}

int isDirectoryExists(const char *path)
{
    struct stat stats;
    stat(path, &stats);

    // Check for file existence
    if (S_ISDIR(stats.st_mode))
{
        return 1;
}
    return 0;
}

int main(int argc, char** argv)
{
if (argc > 2)
{

umask(0);
char b[1];
int fo, ft, nbytes;


nbytes = strlen(argv[2]) + strlen(argv[1]);
char path[nbytes];

if (isDirectoryExists(argv[2]))
{
sprintf(path,"%s/%s", argv[2], argv[1]);
printf("%s\n",path);
if (link(argv[1], path) < 0)
{
err_sys("Link Error");
}
if (unlink(argv[1]) < 0)
{
err_sys("Unlink Error");
}

}
else
{
sprintf(path,"%s/%s", argv[2], argv[1]);
printf("%s\n",path);
mkdir(argv[2], 0777);
if (link(argv[1], path) < 0)
{
err_sys("Link Error");
}
if (unlink(argv[1]) < 0)
{
err_sys("Unlink Error");
}
}

exit(0);
}
else
{
err_sys("not enough arguments");
}
}