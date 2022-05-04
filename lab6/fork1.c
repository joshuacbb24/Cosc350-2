#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <utmp.h>
#include <string.h>


int makeDigit(const char *string)
{
int num = 0;
for (int i = 0; string[i] != '\0'; i++)
{
if(string[i] >= 48 && string[i] <= 57)
{
num = num * 10 + (string[i] - 48);
}
else
{
num = 0;
return num;
}
}
return num;
}
int main (int argc, const char *argv[])
{
if (argc < 5)
{
printf("not enough arguments\n");
exit(1);
}
int Nc = makeDigit(argv[1]);
int Np = makeDigit(argv[2]);
int Tc = makeDigit(argv[3]);
int Tp = makeDigit(argv[4]);
int s;

pid_t pid;
char *message;
int n;
printf("fork program starting\n");
pid = fork();
switch (pid)
{
case -1:
perror("fork failed");
exit(1);
case 0:
message = "This is the child";
n = Nc;
s = Tc;
break;
default:
message = "This is the parent";
n = Np;
s = Tp;
break;
}
for (; n > 0; n--) {
printf("%s\n",message);
sleep(s);
}
exit(0);
}