#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <utmp.h>
#include <string.h>
#include <signal.h>

void signalMessage(int sig)
{
//printf("got here \n");
if(sig == SIGUSR1)
{
printf("Hi Honey! Anything wrong?\n");
}
if(sig == SIGUSR2)
{
//printf("got here in \n");
printf("Do you make trouble again?\n");
}
}

int main(int argc, char* argv[])
{
pid_t pid, pid1;
int status;

if((pid = fork()) < 0)
{
printf("fork failed.");
exit(1);
}
else if(pid == 0)
{
kill(getppid(), SIGUSR1);
_exit(0);
}
else
{
//wait(&status);
if((pid1 = fork()) < 0)
{
printf("fork failed.");
exit(1);
}
else if(pid1 == 0)
{
sleep(1);
kill(getppid(), SIGUSR2);
_exit(0);
}
else
{
signal(SIGUSR1, signalMessage);
signal(SIGUSR2, signalMessage);
pause();
pause();
}
exit(0);
}
}