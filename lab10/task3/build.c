#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "header.h"

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

int main(int argc, char* argv[])
{

union semun arg;
key_t semKey, shmKey;
int semid;
int shmid;
struct Memory *shm;

semKey = ftok("build.c", 'J'); //create a key value
shmKey = ftok(".", 'x'); //create a key value
if((semid=semget(semKey, 3, 0666 | IPC_CREAT))<0){
perror("semget error");
exit(1);
}
//create a shared memory
if ((shmid = shmget(shmKey , sizeof(struct Memory), IPC_CREAT | 0666)) <0)
{
perror("shmget error \n");
exit (1);
}

/*shm = (struct Memory *) shmat(shmid, NULL, 0); //attach to shared memory
if ((long)shm == -1)
{
perror("shmat error \n");
exit (1);
}*/

arg.val = 1;
//set value to the first member of semaphore
if (semctl(semid, MUTEX, SETVAL, arg) == -1)
{
perror("semctl");
exit(1);
}
arg.val = 0;
//set value to the second member of semaphore
if (semctl(semid, FULL, SETVAL, arg) == -1)
{
perror("semctl");
exit(1);
}
arg.val = N;
//set value to the second member of semaphore
if (semctl(semid, EMPTY, SETVAL, arg) == -1)
{
perror("semctl");
exit(1);
}

// Remove the semaphore
if (semctl(semid, 0, IPC_RMID, arg) == -1) 
{
perror("semctl() Error");
exit(1);
}
    return 0;
} 
