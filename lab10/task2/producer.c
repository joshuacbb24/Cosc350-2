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
if ((shmid = shmget(key, sizeof(struct Memory), 0)) <0) //open shared memory
{
perror("shmget error \n");
exit (1);
}
shm = (struct Memory *) shmat(shmid, NULL, 0); //attach to shared memory
if ((long)shm == -1)
{
perror("shmat error \n");
exit (1);
}
memset(shm->data.nums, 0, 5);
shm->count = 0;

while(1){
srand(time(NULL));

if (shm->count != 5)
{
int curr = shm->count;
num = rand() % 10 + 1;
shm->data.nums[curr] = num;
curr++;
shm->count = curr;
//shm->status = FILLED;
}
else
{
printf("No space to insert. \n");
}
for (int s = 0; s < 5; s++) //read available data from the shared memory
{
printf("%d", shm->data.nums[s]);
}
printf("\n");

    }
//shm->gostop = STOP;
shmdt((void *) shm); //detach
return 0;
}