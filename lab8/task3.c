#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <utmp.h>
#include <string.h>
#include <signal.h>

int isNum(char *str)
{
int num = 0;
int valid = 0;

for (int i = 0; str[i] != ' '; i++)
{
//printf("%c\n",str[i]);
if(str[i] == '-' && i == '0')
{
continue;
}
if(str[i] < '0' || str[i] > '9' )
{
num = -1;
break;
}
else
{
num = num * 10 + (str[i] - 48);
}
}
return num;
}

int main()
{
int num, num2, fd[2], total, size;
pid_t pid;
int nbytes, fo, ft, offset;
int stat_val;
pid_t child_pid;
char str[256], str2[256];
char message[] = "Hi, Mom";
char buffer[256];
char buffer2[256];
if (pipe(fd) < 0)
{
printf("fork error");
exit(1);
}
if ((pid = fork()) < 0)
{
printf("fork error");
exit(1);
}
else if (pid == 0)
{
close(fd[1]);		
while ((nbytes = read(fd[0], buffer2, sizeof(buffer2))) > 0)
{
if((size = sscanf(buffer2, "%s%s", &str, &str2)) == 2)
{

strcat(str," ");
printf("the string is %s\n", buffer2);
printf("sscanf is %d\n", size);
printf("str is %s str2 is %s\n", str, str2);

num = isNum(str);

if (num != -1)
{
printf("num is %d\n", num);

strcat(str2," ");
num2 = isNum(str2);
if (num2 != -1)
{
printf("num2 is %d\n", num2);

total = num + num2;
printf("total is %d\n", total);
char *message = (char*) malloc(sizeof(char));
sprintf(message, "The Sum is %d\n", total);
write(STDOUT_FILENO, message, strlen(message));
}
else
{
printf("the string is %s\n", buffer2);
printf("sscanf is %d\n", size);
printf("str is %d str2 is %d\n", str, str2);

write(STDOUT_FILENO,"input 2 is not number\n", 23);
}
}
else
{
printf("the string is %s\n", buffer2);
printf("sscanf is %d\n", size);
printf("str is %d str2 is %d\n", str, str2);

write(STDOUT_FILENO,"input 1 is not number\n", 23);
}

}
else
{
printf("the string is %s\n", buffer2);
printf("sscanf is %d\n", size);
printf("str is %s str2 is %s\n", str, str2);
write(STDOUT_FILENO,"must enter two numbers\n", 24);
}
}

}
else
{
close(fd[0]);
write(STDOUT_FILENO,"enter 2 numbers\n", 17);
sleep(5);
while((nbytes = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0)
{
write(fd[1], buffer, sizeof(buffer));
write(STDOUT_FILENO,"enter 2 numbers\n", 17);
//sleep(5);
}
exit(0);
}
}