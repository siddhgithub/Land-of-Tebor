#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "heroes.h"
#include "locations.h"
#include "simulation.h"
#include "heap.h"
#include "adventuretype.h"

void print_by_level(void* data)
{
/* Nothing to print */
printf("print_by_level\n");

}


void print_by_power(void* data)
{
/* Nothing to print */
printf("print_by_power\n");

}

void print_by_subtlety(void* data)
{
/* Nothing to print */
printf("print_by_subtlety\n");

}

void print_by_strategy(void* data)
{
/* Nothing to print */
printf("print_by_strategy\n");

}

void print_by_charm(void* data)
{
/* Nothing to print */
printf("print_by_charm\n");

}


void print_by_deusex(void* data)
{
/* Nothing to print */
printf("print_by_deusex\n");


}

/*level/power/subtlety/strategy/charm*/

int compare_by_level(void* data1, void* data2)
{
  LocationNode* node1 = (LocationNode*)data1;
  LocationNode* node2 = (LocationNode*)data2;

 return (node2->level - node1->level);
   
}


int compare_by_power(void* data1, void* data2)
{
  LocationNode* node1 = (LocationNode*)data1;
  LocationNode* node2 = (LocationNode*)data2;

 return (node2->rating[Power] - node1->rating[Power]);
   
}



int compare_by_subtlety(void* data1, void* data2)
{
  LocationNode* node1 = (LocationNode*)data1;
  LocationNode* node2 = (LocationNode*)data2;

 return (node2->rating[Subtlety] - node1->rating[Subtlety]);
   
}

int compare_by_strategy(void* data1, void* data2)
{
  LocationNode* node1 = (LocationNode*)data1;
  LocationNode* node2 = (LocationNode*)data2;

 return (node2->rating[Strategy] - node1->rating[Strategy]);
   
}

int compare_by_charm(void* data1, void* data2)
{
  LocationNode* node1 = (LocationNode*)data1;
  LocationNode* node2 = (LocationNode*)data2;

 return (node2->rating[Charm] - node1->rating[Charm]);
   
}

int compare_by_deusex(void* data1, void* data2)
{

LocationNode* node1 = (LocationNode*)data1;
LocationNode* node2 = (LocationNode*)data2;

/* If any player attribute is greter then equal to correspoding location rating 
player wins the location. So arrange locations in inceasing order of rating value 
this would help to player reach highest level*/

int node1_lowest = node1->rating[0];

for(int i = 1; i < 3; i++)
{  
  if(node1->rating[i] < node1_lowest)
   node1_lowest = node1->rating[i];
}

int node2_lowest = node2->rating[0];
for(int i = 1; i < 3; i++)
{  
  if(node2->rating[i] < node2_lowest)
   node2_lowest = node2->rating[i];
}

return node2_lowest - node1_lowest;

}


bool adventure_startgame(int gametype, int threadCount)
{

Heroes* heroes = heroes_initialize();


if(heroes == NULL)
{
  printf("Heroes Initialized Failure\n");
  exit(-1);
}
bool flag =  heroes_load(heroes, "./heroes.lot");
if(flag == false)
{
  printf("Error in heroes_load \n");
  exit(-1);
}

Locations *pLocations = locations_initialize();
if(pLocations == NULL)
{
  printf("locations_initialize Failure\n");
  exit(-1);
}

flag =  locations_load(pLocations, "./locations.lot");
if(flag == false)
{
  printf("Error in locations_load \n");
  exit(-1);
}




Locations* pLocationByType;
char livefileName[50];
char deadfileName[50];

strcpy(livefileName,"./deusex_live_out.txt");
strcpy(deadfileName, "./deusex_dead_out.txt");
pLocationByType = sim_generate_location_param(pLocations, "ByDeusex", &compare_by_deusex, &print_by_deusex );

if(pLocationByType == NULL)
{
printf("sim_generate_location_param: failure for type %d",gametype);
exit(-1);
}
else
{
  printf("Generating output file %s, %s\n",livefileName,deadfileName);

}
Heap* heap = sim_challenge(heroes,pLocationByType,threadCount);
//printf("sim_challenge\n");

if(heap == NULL)
{
printf("Heap is null\n");
exit(-1);
}

sim_createoutfile(heap, pLocationByType, livefileName,deadfileName);
//printf("sim_createoutfile\n");

}
