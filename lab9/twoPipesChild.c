#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[])
{
int data_processed;
char buffer[BUFSIZ + 1];
int file_descriptor, file_descriptor2, file_descriptor3, file_descriptor4;
const char some_data[] = "Hi, Mom";
memset(buffer, '\0', sizeof(buffer));
sscanf(argv[1], "%d", &file_descriptor);
sscanf(argv[2], "%d", &file_descriptor2);
sscanf(argv[3], "%d", &file_descriptor3);
sscanf(argv[4], "%d", &file_descriptor4);
//3 is read
//2 is write
close(file_descriptor);
close(file_descriptor4);
data_processed = read(file_descriptor3, buffer, BUFSIZ);
printf("%d - read %d bytes: %s\n", getpid(), data_processed, buffer);
data_processed = write(file_descriptor2, some_data, strlen(some_data));
printf("%d - wrote %d bytes\n", getpid(), data_processed);

exit(EXIT_SUCCESS);
}

