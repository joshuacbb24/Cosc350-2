#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct my_msgbuf {
long mtype;
int num1;
int num2;
};

int main(void)
{

struct my_msgbuf buf;
int msqid;
int nbytes, numOne, numTwo;
char buffer[BUFSIZ + 1];
key_t key;
/*create a key for create message queue */
if ((key = ftok("msgQsnd.c", 'B')) == -1) {
perror("ftok error");
exit(1);
}

/*create a message queue */
if ((msqid = msgget(key, 0644)) == -1) {
perror("msgget error");
exit(1);
} 

for(;;) {
/* get each message from the message queue */
if (msgrcv(msqid, (struct msgbuf *)&buf, sizeof(buf), 0, 0) == -1) {
perror("msgrcv error");
exit(1);
}
printf("number 1 is: %d \n number 2 is: %d \n the sum is: %d", buf.num1, buf.num2, buf.num1+buf.num2);
}
    return 0;
} 
