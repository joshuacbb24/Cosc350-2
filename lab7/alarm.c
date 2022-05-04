#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

static int alarm_fired = 0;

//signal handler for SIGALRM
void ding(int sig) {
  //printf("ding argument is %d\n", sig);
  alarm_fired = 1;
}

int main(int argc, char *argv[])
{
  pid_t pid;

  struct sigaction act;
  act.sa_handler = ding; // set signal handler as ding
  //clear structure
  //memset (&act, 0, sizeof(act));
  
  printf("alarm application starting\n");
  
  pid = fork();
  switch(pid) {
    case -1:/*failure*/
      perror("fork failed");
      exit(1);
    case 0:/* child */
      sleep(5);
      kill(getppid(), SIGALRM);
      _exit(0);
  }
  
  /* if we get here we are the parent process*/
  printf("waiting for the alarm to go off\n");
  if (sigaction(SIGALRM, &act, NULL)) {
perror ("sigaction");
return 1;
}
  pause();
  if (alarm_fired)
  {
    printf("Ding!\n");
  }
  
  printf("done\n");
  exit(0);
}
  
