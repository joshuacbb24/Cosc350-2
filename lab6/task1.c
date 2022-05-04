#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;
char* mygetenv(char* name)
{
    int size = strlen(name); 
int count = 0;
    char **p = environ;
    

    while (*p != NULL)
    {
int found = 1;
char *string = (char*) malloc( sizeof(char) );
    strcpy(string, p[count]);
for(int i = 0; i < size; i++)
{
//printf("name at %d = %c\n",i,name[i]);
//printf("environ syting at %d = %s\n",i, string);
//printf("environ p at %d = %s\n",i, *p);
if (name[i] != string[i])
{
found = 0;
break;
}
//printf("found is %d\n",found);
}
if (found == 1)
{
//printf("environ is %s\n", string);
//printf("environ is %s\n", *p);
//printf("environ is %s\n", p[count]);
return string;
}
count++;
//*p++;
    }
return NULL;
}

int main(int argc, char** argv)
{
char *p;
if(argc < 2)
{
printf("Not Enough Arguments");
return 1;
} 
if ((p = mygetenv(argv[1])) == NULL)
{
printf("Not An Env Var");
return 1;
}
    printf("Env Var found\n");
    printf("%s\n", p);
//free( p );
    return 0;
}