#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 100

void signal_handler(int sig_num)
{
  /* add case statements for SIGUSR1, SIGUSR2 */
  switch (sig_num)
  {
    case SIGINT:
      printf("\tTry typing something\n");
      fflush(stdout);
      break;
    case SIGALRM:
	    printf("timeout\n");
      fflush(stdout);
	    exit(0);
      break;
    default:
      printf("Don't know how to handle signal %d (%s)\n", sig_num, strsignal(sig_num));
      fflush(stdout);
  }
}

int main(int argc, char** argv)
{
  int timer = 0;
  char* buf = (char*) calloc(BUF_SIZE, sizeof(char));
  size_t size = BUF_SIZE;
  pid_t my_pid = getpid();
  printf("My pid is %d\n", my_pid);

  /* parse value for timer */
  if (argc ==2)
  {
    timer =atoi(argv[1]);
  }
  
  /* install additional signals for USR1 USR2 and HUP */
	signal(SIGALRM, signal_handler);
  signal(SIGINT, signal_handler);
  
  
  if (timer > 0)
  {
    printf("Setting timer for %d seconds\n",timer);
    fflush(stdout);
	  alarm(timer);
  }

  printf("enter you name: ");
	fflush(stdout); /* always use in system programing */
  getline(&buf, &size, stdin);
  printf("Hello %s\n", buf);
  fflush(stdout);
	alarm(0); /* clear alarm before exiting */
  free(buf);
	return 0;
}
