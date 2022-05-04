#include <sys/types.h>
#include <sys/wait.h>
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
int exit_code;

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
exit_code = 37;
break;
default:
message = "This is the parent";
n = Np;
s = Tp;
exit_code = 0;
break;
}
for (; n > 0; n--) {
printf("%s\n",message);
sleep(s);
}
if (pid != 0)
{
int stat_val;
pid_t child_pid;

child_pid = wait(&stat_val);

printf("Child has finished: PID = %d\n", child_pid);
if (WIFEXITED(stat_val))
{
printf("Child exited with code %d\n", WEXITSTATUS(stat_val));
}
else
{
printf("Child terminated abnormally\n");
}
}
exit(exit_code);
}