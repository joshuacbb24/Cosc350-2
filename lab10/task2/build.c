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
key = ftok(".", 'x'); //create a key value
//create a shared memory
if ((shmid = shmget(key, sizeof(struct Memory), IPC_CREAT | 0666)) <0)
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
//shm->status = NOT_READY;
//shm->gostop = GO;
return 0;
}
