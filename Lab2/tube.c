#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define WRITE 1
#define READ 0

int main(int argc, char *argv[])
{
  pid_t child1, child2;
  int status1, status2;
  int pipe[2];
  
  child1 = fork();
  child2 = fork();
  
  pipe(pipe);
  
  waitpid(child1, &status1, WUNTRACED);
  waitpid(child1, &status2, WUNTRACED);
  
  fprintf(stderr, "child 1 %s: $$ = %d\n", child1);
  fprintf(stderr, "child 2 %s: $$ = %d\n", child2);
  
  
}
