#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/times.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static int caught = 0;
static int terminate = 0;
static const char *signals[27] = {"HUP", "INT", "QUIT", "ILL", "TRAP", "ABRT", "IOT", "BUS", "FPE",
                            "USR1", "SEGV", "USR2", "PIPE", "ALRM", "TERM", "STKFLT",
                            "CHLD", "CONT", "TSTP", "TTIN", "TTOU", "URG", "XCPU", "XFSZ",
                            "VTALRM", "PROF", "WINCH"};

void showPID() //The program includes a status line that includes its PID to stderr
{
  int pid = getpid();
  fprintf(stderr, "catcher: $$ = %d\n", pid); 
}

void handler(int num) //Handler emits a line to stdout 
{
  time_t seconds;
  time(&seconds);
  
  if(num == 15){
    terminate++;
  
  }else{
    terminate = 0;
  }
  //Handler emits a line to stdout that indicates the signal caught and the time it was caught
  if(num == SIGUSR1){
  fprintf(stdout, "SIGUSR1 caught at %ld\n", seconds);
  }
  else if(num == SIGUSR2){
    fprintf(stdout, "SIGUSR2 caught at %ld\n", seconds);
  }else{
    fprintf(stdout, "SIG%s caught at  %ld\n",signals[num - 1], seconds);
  }
  caught++;
}
    
    
void checkSig(int argc, char **argv) //The program registers a handler for every for each argument (signal(2))
{
  for(int i = 1; i < argc; i++)
  {
    for(int j = 0; j < 27; j++)
    {
      if(strcmp(argv[i], signals[j] == 0)){
        signal(j + 1, handler);
      }
      if(signal(j + 1, handler) == SIG_ERR){
        fprintf(stderr, "signal error\n");
      }
    }
  }
  while (terminate < 3){
  pause();
  }

  
  //The program emits a final status message to stderr that indicates the # of signals caught       
  fprintf(stderr, "catcher: Total signals count = %d\n", caught);
     
  exit(EXIT_SUCCESS); //Program gracefully terminates after 3 succesve SIGTERM signals
}         
         
  int main(int argc, char** argv)
{
  showPID();
  checkSig(argc, argv);

  return 0;
}
