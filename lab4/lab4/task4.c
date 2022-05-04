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

int main(int argc, char** argv)
{
umask(0);
char b[1];
int fo, ft, nbytes;

char path[] = "/mnt/linuxlab/home/jcobb1/";
chdir(path);

mkdir("/mnt/linuxlab/home/jcobb1/Dir1", 0777);
mkdir("/mnt/linuxlab/home/jcobb1/Dir2", 0777);
mkdir("/mnt/linuxlab/home/jcobb1/Dir2/Dir21", 0777);

fo = open("/mnt/linuxlab/home/jcobb1/cosc350/lab4/hello", O_RDONLY);
ft = open("/mnt/linuxlab/home/jcobb1/Dir2/Dir21/hello", O_WRONLY| O_CREAT, 0777);
while((nbytes = read(fo, b, 1)) > 0)
{
write(ft, b, 1);
}    
if (symlink("/mnt/linuxlab/home/jcobb1/Dir2/Dir21","/mnt/linuxlab/home/jcobb1/Dir1/toDir21") < 0)
{
err_sys("Symbolic Link Creation Error \n");
}
if (symlink("/mnt/linuxlab/home/jcobb1/Dir2/Dir21/hello", "/mnt/linuxlab/home/jcobb1/Dir1/toHello") < 0)
{
err_sys("Symbolic Link Creation Error \n");
}

close(fo);
close(ft);

return 0;
}