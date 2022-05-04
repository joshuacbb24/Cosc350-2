#include <stdio.h> 
#include <string.h> 
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>  
#include <sys/stat.h>
  
int main(int argc,  char** argv) 
{ 
if (argc == 3)
{
int sum = 0;
int size;
int num;
int numarray[argc-1];
int fo, ft, nbytes;
char b[1];
int value;
int c[1];

// open file 1
fo = open(argv[1], O_RDONLY);
//if file opens
if (fo != -1)
{
//create file 2
ft = open(argv[2], O_RDWR | O_CREAT, 0666);
//if file opens
if (ft != -1)
{
while ((nbytes = read(fo, b, 1)) > 0)
{
dup2(ft, 1);
printf("%c", b[0]);
}
close (fo);
close (ft);
}
else
{
printf("file %c already exists\n", argv[2]);
close (fo);
}
}
else
{
printf("file %c does not exist\n", argv[1]);
}
}
else 
{
printf("There are not only two files\n");
}
return 0; 
} 