#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	if(argc < 2){
	exit(EXIT_FAILURE);
	}
	else
	int size = atoi(argv[1]);
	int num;
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++)
		{
			num = (rand() % 201) - 100
			fprintf(stdout, "%4d \n", num);
		}
	
	}
}
