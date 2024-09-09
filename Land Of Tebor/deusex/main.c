#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "heroes.h"
#include "locations.h"
#include "simulation.h"
#include "heap.h"
#include "adventuretype.h"

int main(int argc, char** argv)
{

struct timeval start_time, end_time;
gettimeofday(&start_time, NULL);


if(argc != 2)
{ 
  
 printf("Usage: programname threadcount\n");
 exit (-1);
}

int threadCount;
sscanf(argv[1],"%d",&threadCount);

if(threadCount <= 0)
{
    printf("Minimum threadcount should be 1\n");
    exit(-1);
}    

if(argc == 2)
{
  
  adventure_startgame(0, threadCount);
}  


gettimeofday(&end_time, NULL);

printf("Computing Time micro seconds : %ld\n", ((end_time.tv_sec - start_time.tv_sec)*1000000) + ( end_time.tv_usec - start_time.tv_usec));

return 0;
}
