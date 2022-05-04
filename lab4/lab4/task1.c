#include <stdio.h> 
#include <string.h> 
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>  
#include <sys/stat.h>
  
int main(int argc,  char** argv) 
{ 
if (argc > 2)
{
umask(0);
int sum = 0;
int size;
char num = 0;
int numarray[argc-1];
int fo, ft, nbytes;
char b[1];
char *buff;
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
dup2(ft,1);
while ((nbytes = read(fo, b, 1)) > 0)
{
if (b[0] == ' ')
{
printf("%c", num);
num = 0;
continue;
}
num = num * 10 + (b[0] - '0');
//printf("num is %d\n", num);

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