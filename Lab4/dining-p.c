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

static int finish;
sem_t* side1;
sem_t* side2;
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
  signal(SIGTERM, sigHandler);
  finish = 1;
}

void killSem()
{
  sem_close(side1);
  sem_close(side2);
  
  sem_unlink(CS1);
  sem_unlink(CS2);
  
  sem_destroy(side1);
  sem_destroy(side2);
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
    side1 = sem_open(CS1, O_CREAT, 0660, 1);
    side2 = sem_open(CS2, O_CREAT, 0660, 1);
    
    do
    {
      sem_wait(side1);
      sem_wait(side2);
      
      eat(phil);
      
      sem_post(side1);
      sem_post(side2);
      
      think(phil);
      
      cyCount++;
    }
    
  while(finish);
  if(finish != 1)
  {
    fprintf(stderr, "Philospher #%d completed %d cycles.\n", phil, cyCount);
  }
    
   killSem();
  }

  return 0;
}
    
