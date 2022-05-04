#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <utmp.h>
#include <string.h>


int makeDigit(char string)
{
int num = 0;
if(string >= 48 && string <= 57)
{
return 1;
}
else
{
return 0;
}
}

int main(int argc,const char* argv[])
{
int exit_code;
pid_t pid;
int fo, fc, fp, nbytes, cp, cc, offset1, offset2;
char buf[1];
char bufp[1];
umask(0);
char *message;
int n, s;


if((fo = open(argv[1], O_RDONLY)) == -1)
{
printf("file open error");
exit(1);
}
//printf("got here\n");
pid = fork();
switch (pid)
{
case -1:
//printf("got here\n");
perror("fork failed");
exit(1);
case 0:
//printf("got here2\n");

if((fc = open("child.txt", O_WRONLY|O_CREAT, 0777)) == -1)
{
printf("file open error");
exit(1);
}
//printf("got here4\n");
offset1 = 0;
//printf("got here6\n");
while(pread(fo, buf, 1, offset1) > 0)
{
//printf("got here8\n");
if(!makeDigit(buf[0]))
{
write(fc, buf, 1);
}
offset1++;
}
default:
//printf("got here3\n");

if((fp = open("parent.txt", O_WRONLY|O_CREAT, 0777)) == -1)
{
printf("file open error");
exit(1);
}
//printf("got here5\n");
offset2 = 0;
//printf("got here7\n");
while(pread(fo, bufp, 1, offset2) > 0)
{
//printf("got here9\n");
if(makeDigit(bufp[0]))
{
write(fp, bufp, 1);
}
offset2++;
}
}
if (pid != 0)
{
close(fo);
close(fc);
close(fp);
/*int stat_val;
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
*/
}
exit(0);
}