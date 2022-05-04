 
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
int main()
{
int data_processed;
int status;
int file_pipes[2];
int file_pipes2[2];

const char some_data[] = "Hi there, Kiddo";
char buffer[BUFSIZ + 1];
char buffer2[BUFSIZ + 1];
char buffer3[BUFSIZ + 1];
char buffer4[BUFSIZ + 1];
pid_t fork_result, result;
memset(buffer, '\0', sizeof(buffer));
if (pipe(file_pipes) == 0) {
pipe(file_pipes2);
fork_result = fork();
if (fork_result == (pid_t)-1) {
fprintf(stderr, "Fork failure");
exit(EXIT_FAILURE);
}
if (fork_result == 0) {
sprintf(buffer, "%d", file_pipes[0]);
sprintf(buffer2, "%d", file_pipes[1]);
sprintf(buffer3, "%d", file_pipes2[0]);
sprintf(buffer4, "%d", file_pipes2[1]);
(void)execl("twoPipesChild", "twoPipesChild", buffer, buffer2, buffer3, buffer4, (char *)0);
exit(EXIT_FAILURE);
}
else {
close(file_pipes[1]);
close(file_pipes2[0]);

data_processed = write(file_pipes2[1], some_data, strlen(some_data));
printf("%d - wrote %d bytes\n", getpid(), data_processed);
//result = wait(&status);
data_processed = read(file_pipes[0], buffer, sizeof(buffer));
printf("%d - read %d bytes: %s\n", getpid(), data_processed, buffer);

}
}
exit(EXIT_SUCCESS);
}
