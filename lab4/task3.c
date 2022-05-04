#include <stdio.h> 
#include <string.h> 
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>  
#include <sys/stat.h>
//#include <ctype.h>

int isdigit(int a)
{
if(a >= '0' && a <= '9')
{
return 1;
}
else
{
return 0;
}
}

int convIntToStr(char * str, int x)
{
sprintf(str, "%d", x);
return (strlen(str));
}
int main(int argc,  char** argv) 
{ 
if (argc == 2)
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
while ((nbytes = read(fo, b, 1)) > 0)
{
val = b[0];
if (isdigit(val))
{
//printf("dig is %d\n", val);
ar[position] = b[0];
position++;
}
}
ar[position] = '\0';
for (int i = 0; ar[i] != '\0'; i++)
{
num = num * 10 + (ar[i] - 48);
//printf("num is %d\n", num);
}
num = num + 10;
length = convIntToStr(ar, num);
write(1, ar, length);
printf("\n");
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