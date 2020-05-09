#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/wait.h>

#define CS1 "/chopstick1"
#define CS2 "/chopstick2"

sem_t* stick1;
sem_t* stick2;
static int finish;

void eat(int n){
  fprintf(stdout,"Philosopher #%d is eating\n", n);
  usleep(rand() % 1000000);
}

void think(int n){
  fprintf(stdout, "Philosopher #%d is thinking\n", n);
  usleep(rand() % 1000000);
}

void sigHandler(int sig)
{
  signal(SIGTERM, sig);
  finish = 1;
}

void killSem() //Develop a handler for SIGTERM
{
  sem_close(stick1); //Program needs to effectively release any system resources
  sem_close(stick2);
  
  sem_unlink(CS1);
  sem_unlink(CS2);
  
  sem_destroy(stick1);
  sem_destroy(stick2);
}


int main(int argc, char** argv)
{
 int seats = atoi(argv[1]);
 int phil = atoi(argv[2]);
 
  if(argc < 3)
 {
   printf("Not enough args\n");
    exit(EXIT_FAILURE);
 }
  
  if(phil > seats)
  {
    printf("Not enough seats");
  }
  else if(argc == 3)
  {
    int cyCount = 0;
    signal(SIGTERM, sigHandler);
    
    //Add semaphores to the program
    stick1 = sem_open(CS1, O_CREAT, 0660, 1); //allocate a semaphore for each chopstick
    stick2 = sem_open(CS2, O_CREAT, 0660, 1); 
    
    do
    {
      sem_wait(stick1); //modify the wait() function to wait on the semaphore
      sem_wait(stick2);
      
      eat(phil);       //Augment the code to use the eat function
      
      sem_post(stick1); //modify the signal() function to post to the semaphore
      sem_post(stick2);
      
      think(phil);     //Augment the code to use the think function
      
      cyCount++; //Augment the code to keep a count of the number of full eat-think cycles
    }
    
  while(finish);
  if(finish != 1)
  {
    fprintf(stderr, "Philospher #%d completed %d cycles.\n", phil, cyCount); //program needs to emit a line to stderr the following line
  }
    
   killSem();
  }

  return 0;
}
    
