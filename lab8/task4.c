#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>


int main(int argc, char* argv[])
{

if (argc < 3)
{
printf("not enough arguments\n");
return 1;
}

char *cmd = (char*) malloc( argc * sizeof(char) );
char buf[BUFSIZ]; /* BUFSIZ =1024 defined in stdio.h */
FILE *ptr;

for(int i = 1; i < argc; i++)
{
sprintf(cmd, "%s %s", cmd, argv[i]);
}
//wfp = popen(cmd, "r");
if ((ptr = popen(cmd, "r")) != NULL)
{
while (fgets(buf, BUFSIZ, ptr) != NULL)
{
(void) printf("%s", buf);
}
}
pclose(ptr);
return 0;
}