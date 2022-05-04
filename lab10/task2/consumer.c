#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<errno.h>
#include "header.h"
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(int argc, char *argv[])
{
int shmid;
key_t key;
struct Memory *shm;
char name[20];
char buffer[BUFSIZ + 1];
int n, id, more, i, nbytes;
int num, num2;
key = ftok(".", 'x'); //get key value
// open existing shared memory
if ((shmid = shmget(key, sizeof(struct Memory), 0)) <0)
{
perror("shmget error \n");
exit (1);
}
//a pointer is attach to shared memory
shm = (struct Memory *) shmat(shmid, NULL, 0);
if ((long)shm == -1)
{
perror("shmat error \n");
exit (1);
}

while(1)
{
if (shm->count != 0)
{
int curr = shm->count;
shm->data.nums[curr] = 0;
curr--;
shm->count = curr;
}
else
{
printf("Nothing to remove. \n");
}
for (int s = 0; s < 5; s++) //read available data from the shared memory
{
printf("%d", shm->data.nums[s]);
}
printf("\n");
}
shmdt((void *) shm); //detach
return 0;
}
