#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/times.h>

int getSTART()  //Gets start time (time(2))
{
  time_t START;
  time(&START);
  return START;
}

int main()
{
  time_t STOP;
  pid_t wchild;
  pid_t child;
  int status;
  struct tms tms_START, tms_STOP;
  
  getSTART();
  times(&tms_START);
  printf("START: %d\n", getSTART());
 
  child = fork(); //fork(2)
  
  //When the return value of fork() return 0
  if(child == 0) 
  {
    printf("PPID: %d, ", getppid()); //PID of Parent (getppid(2))
    printf("PID: %d, ", getpid()); //Own Pid (getpid(2))
    times(&tms_STOP); //gets end time of process
    exit(EXIT_SUCCESS); //(exit(3))
   }
   
   //In case return value of fork() is positive
  else if(child > 0)
  {
    wchild = waitpid(child, &status, WUNTRACED); //To get pid of child and return status val (waitpid(2))
    
    //CPID and Return status are applicable in this scenario therefore CPID and RETVAL are shown
    printf("PPID: %d, PID: %d, CPID: %d, RETVAL: %d\n", getppid(), getpid(), wchild, status);
    times(&tms_STOP); //gets end time of process
   }
  
  //If return value of fork() is a negative
  else
  {
    printf("Fork Unavailable");
  }
  
  //Prints User/System time and Child User/System time
  printf("USER: %ld, SYS: %ld\n", (tms_STOP.tms_utime - tms_START.tms_utime), (tms_STOP.tms_stime - tms_START.tms_stime));
  printf("CUSER: %ld, CSYS: %ld\n", (tms_STOP.tms_cutime - tms_START.tms_cutime), (tms_STOP.tms_cstime - tms_START.tms_cstime));

  //Gets and prints stop time
  time(&STOP);
  printf("STOP: %ld", STOP);
}

