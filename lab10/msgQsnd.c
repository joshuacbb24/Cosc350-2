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
if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
perror("msgget error");
exit(1);
} 

printf("MsgRec: ready to receive messages.\n");
buf.mtype = 1;
printf("Enter two numbers \n");

while((nbytes = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0)
{
if(sscanf(buffer, "%d%d", &buf.num1, &buf.num2) == 2)
{
if (msgsnd(msqid, (struct msgbuf *)&buf, sizeof(buf), 0) == -1)
{
    perror("msgsnd error");
}
write(STDOUT_FILENO,"enter 2 numbers\n", 17);
}
else
{
printf("Error, input must be two numbers\n");
printf("Enter two numbers \n");
continue;
}

}

/* Now remove message queue by calling msgclt */
if (msgctl(msqid, IPC_RMID, NULL) == -1) {
perror("msgctl error");
exit(1);
}
exit(0);

}