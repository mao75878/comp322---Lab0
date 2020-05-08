#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *[]){
  FILE *logfile = fopen("lab6.log", "a");
  fprintf(logfile, "Pop %s\n", argv[0]);
  fclose(logfile);
  return 0;
}
