#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/times.h>
#include <stdlib.h>
#include <string.h>

static int count = 0;
static int terminate = 0;
static char *signals[27] = {"HUP", "INT", "QUIT", "ILL", "TRAP", "ABRT", "BUS", "FPE",
                            "KILL", "USR1", "SEGV", "USR2", "PIPE", "ALRM", "TERM", "STKFLT",
                            "CHLD", "CONT", "STOP", "TSTP", "TTIN", "TTOU", "URG", "XCPU", "XFSZ",
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
  }
  else{
    terminate = 0;
  }
  if(num == SIGUSR1)
  {
  fprintf(stdout, "SIGUSR1 caught at %ld\n", seconds);
  }
  else if(num == SIGUSR2){
    fprintf(stdout, "SIGUSR2 caught at %ld\n", seconds);
  }
  else{
    fprintf(stdout, "SIG%s caught at  %ld\n", seconds);
  }
  count++;
}
    
    
void checkSig(int argc, char **argv) //The program registers a handler for every for each argument
{
  for(int i = 1; i < argc; i++)
  {
    for(int j = 0; j < 27; j++)
    {
      if(strcmp(argv[i], signals[j] == 0){
        signal(j + 1, handler);
      }
         }
         }
         
         
  int main(int argc, char** argv)
{
  showPID();
}
