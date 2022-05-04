#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <utmp.h>
int openUtmpFile()
{
int fd;
if ((fd = open(UTMP_FILE, O_RDONLY)) == -1)
{
printf("File does not exist.\n");
return fd;
}
return fd;
}
int main ( )
{
int count = 0, nbytes;
struct utmp current_record;
int reclen = sizeof(struct utmp);
int fd = openUtmpFile();

while ((nbytes = read(fd, &current_record,reclen)) > 0)
{
if (current_record.ut_type == USER_PROCESS)
{
printf("%s\n",current_record.ut_user);
count++;
}
}
printf("The number of logged in users is %d\n", count);
close(fd);
return 0;
}