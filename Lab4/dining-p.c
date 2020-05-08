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


void eat(int n){
  fprintf(stdout,"Philosopher #%d is eating\n", n);
  usleep(rand() % 1000000);
}

void think(int n){
  fprintf(stdout, "Philosopher #%d is thinking\n", n);
  usleep(rand() % 1000000);
}

  
