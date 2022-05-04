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
int Nc = makeDigit(argv[1]);
int Tc = makeDigit(argv[2]);

for (; Nc > 0; Nc--) {
printf("Child PID: = %d message: %s\n", getpid(), argv[0]);
sleep(Tc);
}

exit(37);
}