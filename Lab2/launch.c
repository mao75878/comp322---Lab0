#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
  pid_t child;
  int status;
  child = fork(); //the program forks a child process (see fork(2))
  
  if(child > 0)
  {
  fprintf(stderr, "%s: $$ = %d\n", argv[1], child); //The parent process prints the PID of the child on stderr
  
  waitpid(child, &status, WUNTRACED);                 //The parent prints the return value of the child on stderr
  fprintf(stderr, "%s: $? = %d\n", argv[1], status);   //(see waitpid(2))
  }
  
  else if(child == 0)
  {
    execve(argv[1], argv + 1, NULL); //The child process executes the supplied command (see execve(2))
  }
  
  else
  {
    printf("Fork Unavailable");
  }
  
  return 0;
}
