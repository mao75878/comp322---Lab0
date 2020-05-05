#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>


int find(int argc, char* argv[]) //To find the second argument
{
  int argCheck;
  for(int i = 0; i < argc; i++)
  {
    if(strcmp(argv[i], ",") == 0)
       {
         argv[i] = NULL;
         argCheck = i + 1;
       }
   }
       return argCheck;
 }
       
int main(int argc, char *argv[])
{
  pid_t child1, child2;
  int status1, status2;
  int pipefd[2];
  int arg2;
  
  arg2 = find(argc, argv);
  
  pipe(pipefd); //The program allocates a pipe
  
  if(pipe(pipefd) == -1)// If pipe fails
  {
    fprintf(stderr, "Pipe Error");
    exit(EXIT_FAILURE);
  }
  
  child1 = fork(); //The program forks 2 children 
  child2 = fork();
  
  if(child1 == 0) //The first child executes the 1st (Check for 1st child)
  {
    dup2(pipefd[1], 1);
    execve(argv[1], argv + 1, NULL);
  }
  
  else if(child1 < 0) //If fork 1 fails
  {
    printf("Fork Error");
    exit(EXIT_FAILURE);
  }
  
  //Checks for when child1 is > 0)
  else{
    if(child2 == 0) //Second child process executes the second process
    {
      dup2(pipefd[0], 0);
      execve(argv[arg2], argv + arg2, NULL);
    }
    else if(child2 > 0) //This is the parent
    {
    
      fprintf(stderr, "child 1 %s: $$ = %d\n", argv[1], child1); //The parent process prints the PID of both children 
      fprintf(stderr, "child 2 %s: $$ = %d\n", argv[arg2], child2);
    
      close(pipefd[1]);  //The parent process closes access to the pipe
      close(pipefd[0]);
    
      waitpid(child1, &status1, WUNTRACED);
      waitpid(child1, &status2, WUNTRACED);
    
      //The program prints the return val of the first child then the second child
      fprintf(stderr, "child 1 %s: $? = %d\n", argv[1], status1);
      fprintf(stderr, "child 2 %s: $? = %d\n", argv[arg2], status2);
    }
   else //If fork 2 fails
   {
     printf("Fork Error");
     exit(EXIT_FAILURE);
   }
  }
}
               
     
             
  
   
  
