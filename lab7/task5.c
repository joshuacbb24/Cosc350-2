#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <utmp.h>
#include <string.h>
#include <signal.h>

void hdl (int sig)
{
signal(SIGQUIT, SIG_DFL);
}

int main (int argc, char *argv[])
{
int i;
sigset_t mask;
sigset_t orig_mask;
struct sigaction act;
memset (&act, 0, sizeof(act)); //clear structure
act.sa_handler = hdl; // set signal handler as hd1
sigemptyset (&mask); // clear signal set
sigaddset (&mask, SIGINT); // add SIGINT
sigaddset (&mask, SIGQUIT); // add SIGQUIT

// SIGINT & SIGQUIT are blocked
if (sigprocmask(SIG_BLOCK, &mask, &orig_mask) < 0) {
perror ("sigprocmask");
return 1;
}
for(i = 0; i < 5; i++)
{
printf("%d\n", i+1);
sleep(1);
}
signal(SIGQUIT, hdl );
signal(SIGINT, SIG_IGN);
// SIGINT & SIGQUIT are unbloked
/*if (sigprocmask(SIG_SETMASK, &orig_mask, NULL) < 0) {
perror ("sigprocmask");
return 1;
}*/
if (sigprocmask(SIG_UNBLOCK, &mask, NULL) < 0) {
perror ("sigprocmask");
return 1;
}

sigemptyset (&orig_mask); // clear signal set
sigemptyset (&mask); // clear signal set
sigaddset (&mask, SIGINT); // add SIGINT
if (sigprocmask(SIG_BLOCK, &mask, &orig_mask) < 0) {
perror ("sigprocmask");
return 1;
}

for(i = 0; i < 5; i++)
{
printf("%d\n", i+1);
sleep(1);
}
return 0;
}
