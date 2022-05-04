#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>

void* taction2(void* arg) {
int num2, fnum = 1;
num2 = (int)arg;
	
//printf("number is %d\n",num2);
for(int i = 1; i <= num2; i++)
{
fnum = fnum * i;
}
printf("The product of numbers is %d\n", fnum);
pthread_exit(NULL);
}

void* taction1(void* arg) {
int num2, fnum = 0;
num2 = (int)arg;
	
for(int i = 1; i <= num2; i++)
{
fnum = fnum + i;
}
printf("The sum of numbers is %d\n", fnum);
pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

if (argc < 2)
{
printf("not enough arguments\n");
return 1;
}

pthread_t thread1, thread2;
pthread_t mainthread = pthread_self();
int check, num;

num = atoi(argv[1]);
if ((check = pthread_create(&thread1, NULL, taction1, (void*) num)) != 0) {
printf("first thread creation error");
return 1;
}
if ((check = pthread_create(&thread2, NULL, taction2, (void*) num)) != 0) {
puts("second thread creation error");
return 1;
}

pthread_exit(NULL);
return 0;
}