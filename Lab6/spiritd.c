#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <time.h>
#include <limits.h>
#include <wait.h>

pid_t mole1;
pid_t mole2;
char* path;

void createMole() 
{
  srand(time(0));
  int random = rand() % 2;
  char* molNum;
  char *args[3]; 
  
  //When a new mole is created the following steps are followed:
  if(random == 1)
  {
   mole1 = fork(); //fork a new process
   molNum = "mole1"; //determine child process #
   
    if(mole1 == 0)
   {
     args[0] = path;
     args[1] = molNum;
     args[2] = NULL;
     execv(args[0], args); //execute the program mole
   }
    
    else
    {
      mole2 = fork(); //fork a new processs
      molNum = "mole2"; //determine child process #
      
      if(mole2 == 0)
      {
        args[0] = path;
        args[1] = molNum;
        args[2] = NULL;
        execv(args[0], args); //execute the program mole
      }
    }
  }
}

void sigHandler(int sig)
{
  signal(sig, sigHandler);
  
  if(sig == SIGTERM){ //Upon SIGTERM the program kills all child processes and shutdowns 
    
     //kills both child processes 
    kill(mole1, SIGKILL);
    kill(mole2, SIGKILL);
    
    //kills daemon
    kill(getpid(), SIGKILL); 
  }
  
  //Upon SIG_USR1 the program will
  else if(sig == SIGUSR1)
  {
    kill(mole1, SIGKILL); //kill child process 1
    createMole(); //randomly create either mole1 or mole2 if it does not already exist
  }
  
  //Upon SIG_USR2 the program will
  else if(sig == SIGUSR2)
  {
    kill(mole2, SIGKILL); //kill child process 2
    createMole(); //randomly create either mole1 or mole2 if it does not already exist
  }
   
    
}
  

int main()
{
  struct rlimit lim;
  
  umask(0); //1. Set the file creation mask to 0
  
  pid_t parent; 
  parent = fork(); //2. Fork the parent and have the parent exit
  
  if(parent > 0){ 
    exit(EXIT_SUCCESS);
  }
  
  setsid(); //3. create a new session
  
  chdir("~/"); //4. Change the current working directory to be "/"
  if(chdir("~/") < 0){
    printf("Failure to change directory to /\n");  
    exit(EXIT_FAILURE);
  }
  
  getrlimit(RLIMIT_NOFILE, &lim);  //5. Closes all unneeded file descriptors
  if(lim.rlim_max == RLIM_INFINITY){
    lim.rlim_max = 1024;
  }
  
  for(unsigned int i = 0; i < lim.rlim_max; i++){
    close(i);
  }
  
  open("/dev/null", O_RDWR);  //6. Reopen the standard file descriptors to map to /dev/null
  dup(0);
  dup(0);

  return 0;
}

  
  
  
    
    
    
   
  
  
 
  
    
    
  
