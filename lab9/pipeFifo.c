#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

const int READ_END = 0;
const int WRITE_END = 1;

int main()
{
int data_processed, fo;
int file_pipes[2];
const char some_data[] = "123";
char *buffer = (char*)malloc(sizeof(char));
memset(buffer, '\0', sizeof(buffer));

mkfifo("/tmp/task4_fifo", 0777);
fo = open("/tmp/task4_fifo", O_RDWR);


data_processed = write(fo, some_data, strlen(some_data));
printf("Wrote %d bytes\n", data_processed);
data_processed = read(fo, buffer, sizeof(buffer));
printf("Read %d bytes: %s\n", data_processed, buffer);
exit(EXIT_SUCCESS);
}
