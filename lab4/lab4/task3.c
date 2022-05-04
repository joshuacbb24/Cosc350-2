#include <stdio.h> 
#include <string.h> 
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>  
#include <sys/stat.h>
//#include <ctype.h>


int palind(int fd1, int fd2)
{
char b[1];
char c[1];
int ispal;
int newoff = 1, nbytes;

int offset = lseek(fd1, -1, SEEK_END);
while((nbytes = read(fd2, c, 1)) > 0)
{
lseek(fd1, offset, SEEK_SET);
read(fd1, b, 1);
if(b[0] == c[0])
{
offset = offset - 1;
lseek(fd2, newoff++, SEEK_SET);
continue;
}
else
{
return 0;
}
}
return 1;
}

int main(int argc,  char** argv) 
{ 
if (argc > 1)
{
int val = 0;
int length = 0;
int size;
int num = 0;
int numarray[argc-1];
int fo, ft, nbytes;
char b[1];
int value;
int c[1];
char ar[80];
int position = 0;

// open file 1
fo = open(argv[1], O_RDONLY);
//if file opens
if (fo != -1)
{
ft = dup(fo);
if (ft != -1)
{
if (num = palind(fo, ft))
{
printf("it is a palindrom\n");
}
else 
{
printf("it is not a palindrom\n");
}
}
else
{
printf("file duplication error\n", argv[2]);
}
}
else
{
printf("file %c does not exist\n", argv[1]);
}
}
else 
{
printf("Not enough arguments\n");
}
return 0; 
} 