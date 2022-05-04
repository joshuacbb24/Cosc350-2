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
#include <sys/ipc.h>
#include <sys/sem.h>


#define N 10
typedef int semaphore;
semaphore MUTEX = 1;
semaphore EMPTY = N;
semaphore FULL = 0;

union semun {
int val; /* for SETVAL */
struct semid_ds *buf; /* for IPC_STAT and IPC_SET */
unsigned short *array; /* for GETALL and SETALL */
};

void down(int semId, int index)
{
struct sembuf buf = {index, -1, 0};
semop(semId, &buf, 1);
}
void up(int semId, int index)
{
struct sembuf buf = {index, 1, 0};
semop(semId, &buf, 1);
}

int main(int argc, char *argv[])
{
int shmid, semid;
key_t semKey, shmKey;
struct Memory *shm;
char name[20];
char buffer[BUFSIZ + 1];
int n, id, more, i, nbytes;
int num, num2;

shmKey = ftok(".", 'x'); //get key value
semKey = ftok("build.c", 'J');

if ((shmid = shmget(shmKey, sizeof(struct Memory), 0)) <0) //open shared memory
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

if ((semid = semget(semKey, 1, 0)) == -1) {
perror("semget");
exit(1);
}

memset(shm->data.nums, 0, 5);
shm->count = 0;

while(1){
srand(time(NULL));
down(semid, EMPTY);
down(semid, MUTEX);
int curr = shm->count;
num = rand() % 10 + 1;
shm->data.nums[curr] = num;
curr++;
shm->count = curr;
up(semid, MUTEX);
up(semid, FULL);
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