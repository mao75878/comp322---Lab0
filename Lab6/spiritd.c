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

pid_t mole1;
pid_t mole2;

void sigHandler(int sig)
{
  signal(sig, sigHandler);
  
  if(sig == SIGTERM){
    int mole1_stat = waitpid(mole1, &mole1_stat, WNOHANG);
    int mole2_stat = waitpid(mole2, &mole2_stat, WNOHANG);
    
    if(mole1_stat == 0){
      kill(mole1, SIGKILL);
    }
    
    if(mole2_stat == 0){
      kill(mole2, SIGKILL);
    }
    
    kill(getpid(), SIGKILL);
  }
}

int main(int argc, char **argv)
{
  struct rlimit lim;
  
  umask(0); //Set the file creation mask to 0
  
  pid_t parent; 
  parent = fork(); //Fork the parent
  
  if(parent > 0){
    exit(EXIT_SUCCESS);
  }
  
  chdir("/");
  
  getrlimit(RLIMIT_NOFILE, &lim);  //Closes all unneeded file descriptors
  if(lim.rlim_max == RLIM_INFINITY){
    lim.rlim_max = 1024;
  }
  
  for(unsigned int i = 0; i < lim.rlim_max; i++){
    close(i);
  }
  
  open("/dev/null", O_RDWR);  //Reopen the standard file descriptors to map to /dev/null
  dup(0);
  dup(0);

  return 0;
}

  
  
  
    
    
    
   
  
  
 
  
    
    
  
