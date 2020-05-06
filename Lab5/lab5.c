#include <stdio.h>
#include <stdlib.h>

//computes page number and prints it
void getpNum(unsigned int address, int pSize) 
{
  unsigned int pNum;
  pNum = address/ pSize;
  printf("page number = %d\n", pNum);
}

//computes offset and prints it
void getOffset(unsigned int address, int pSize){ 
  unsigned int offset;
  offset = address % pSize;
  printf("offset = %d\n", offset);
}  
  
int main(int argc, char **argv){

const int pSize = 4096; //4KB = 4096
unsigned int address;
    
if(argc == 2){
  address = atoi(argv[1]); //convert argv[1] to int for address
  printf("The address %d contains:\n", address); //prints address
  getpNum(address, pSize); //explained above
  getOffset(address, pSize); //explained above
}
  else{
    printf("Error: Wrong # of args");
  }  
}
