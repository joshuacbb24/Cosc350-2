#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>

int scores[20];
int numScores = 0;
int total = 0;

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void* taction1(void* arg)
{
int num;


for (int i = 0; i < 20; i++)
{
printf("enter score or negative number to quit\n");
scanf("%d", &num);
if (num < 0 ) 
{
break;
}
scores[i] = num;
total = total + num;
numScores++;
}
pthread_exit(NULL);
}

void* taction2(void* arg)
{
int num2, fnum = 0;
int half = numScores/2;
float median;


if (numScores == 0)
{
printf("the average is 0\n");	
printf("the median is 0\n");	
pthread_exit(NULL);
}
   int i, j;
   for (i = 0; i < numScores-1; i++) 
{      
       for (j = 0; j < numScores-i-1; j++)
{ 
           if (scores[j] > scores[j+1])
{
              swap(&scores[j], &scores[j+1]);
}
}
}

float average = total/numScores;
printf("the average is %f\n", average);
if (numScores % 2 != 0)
{
median = scores[half];
printf("the median is %f\n", median);	
pthread_exit(NULL);
}
else
{
median = (scores[(numScores-1)/2] + scores[half])/2.0;
printf("the median is %f\n", median);
pthread_exit(NULL);
}
}

void* taction3(void* arg)
{
int num2, fnum = 0;

if (numScores == 0)
{
printf("the min is 0\n");	
printf("the max is 0\n");	
pthread_exit(NULL);
}

num2 = scores[0];
fnum = scores[numScores-1];
printf("the min is %d\n", num2);
printf("the max is %d\n", fnum);
pthread_exit(NULL);
}

void* taction4(void* arg)
{
int num2, fnum = 0;
for(int i = 0; i < 20; i++)
{
scores[i] = 0;
printf("%d\n", scores[i]);
}
pthread_exit(NULL);
}


int main(int argc, char *argv[]) {

pthread_t thread1, thread2, thread3, thread4;
pthread_t mainthread = pthread_self();
int check, num;
void *tret1;

if ((check = pthread_create(&thread1, NULL, taction1, NULL)) != 0) {
printf("first thread creation error");
return 1;
}

pthread_join(thread1, NULL);

if ((check = pthread_create(&thread2, NULL, taction2, NULL)) != 0) {
puts("second thread creation error");
return 1;
}
if ((check = pthread_create(&thread3, NULL, taction3, NULL)) != 0) {
puts("third thread creation error");
return 1;
}

pthread_join(thread2, NULL);
pthread_join(thread3, NULL);

if ((check = pthread_create(&thread4, NULL, taction4, NULL)) != 0) {
puts("fourth thread creation error");
return 1;
}

pthread_exit(NULL);
return 0;
}