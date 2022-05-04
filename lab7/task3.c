#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <utmp.h>
#include <string.h>
#include <signal.h>

int main()
{
pid_t pid;
int nbytes, fo, ft, offset;
int stat_val;
pid_t child_pid;
char *newmessage;
char message[] = "Hi, Mom";
char buf[10];

if((fo = open("foo", O_RDWR|O_CREAT, 0777)) < 0)
{
printf("file create error");
exit(1);
}

if ((pid = fork()) < 0)
{
printf("fork error");
exit(1);
}
else if (pid == 0)
{		
if((write(fo, message, strlen(message))) < 0)
{
printf("write error");
exit(1);
}

_exit(0);

}
else
{	
wait(&stat_val);
lseek(fo, 0, SEEK_SET);
if((read(fo, buf, sizeof(buf))) < 0)
{
printf("read error");
exit(1);
}
sprintf(newmessage,"My son said, %s", buf);
printf("%s\n", newmessage);
close(fo);
exit(0);
}
}