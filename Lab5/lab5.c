#include <stdio.h>
#include <stdlib.h>

void getpNum(unsigned int address, int pSize)
{
  unsigned int pNum;
  pNum = address/ pSize;
  printf("page number = %d\n", pNum)
}

getOffset(unsigned int address, int pSize){
  unsigned int offset;
  offset = address % pSize;
  printf("offset = %d\n", offset);
  
  
int main(int argc, char **argv){

const int pSize = 4096;
unsigned int address;
    
if(argc == 2){
  address = atoi(argv[1]);
  printf("The address %d contains:"\n);
  getpNum(address, pSize);
  getOffset(address, pSize);
  
}
  
 
