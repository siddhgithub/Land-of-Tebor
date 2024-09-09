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


if(argc < 2 || argc > 3)
{ 
  
 printf("Usage: programname threadcount level/power/subtlety/strategy/charm \n");
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
  printf("Playing for default option \"level\"\n");
  adventure_startgame(0, threadCount);
}  
/*level/power/subtlety/strategy/charm*/
else if (strcmp(argv[2],"level")==0) 
    adventure_startgame(0, threadCount);
else if (strcmp(argv[2],"power")==0) 
    adventure_startgame(1, threadCount);
else if (strcmp(argv[2],"subtlety")==0) 
    adventure_startgame(2, threadCount);
else if (strcmp(argv[2],"strategy")==0) 
    adventure_startgame(3, threadCount);
else if (strcmp(argv[2],"charm")==0) 
    adventure_startgame(4, threadCount);
else
{
  printf("Invalid option %s \n", argv[2]);
  printf("Usage: programname threadcount level/power/subtlety/strategy/charm \n");
  exit(-1);
}

gettimeofday(&end_time, NULL);

printf("Computing Time micro seconds : %ld\n", ((end_time.tv_sec - start_time.tv_sec)*1000000) + ( end_time.tv_usec - start_time.tv_usec));

return 0;
}
