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

switch(gametype)
{
/*level/power/subtlety/strategy/charm*/

case 0: 
/* type level */
strcpy(livefileName,"./level_live_out.txt");
strcpy(deadfileName, "./level_dead_out.txt");
pLocationByType = sim_generate_location_param(pLocations, "ByLevel", &compare_by_level, &print_by_level );
break;

case 1: 
/* type power */
strcpy(livefileName,"./power_live_out.txt");
strcpy(deadfileName, "./power_dead_out.txt");
pLocationByType = sim_generate_location_param(pLocations, "ByPower", &compare_by_power, &print_by_power );
break;

case 2: 
/* type subtlety */
strcpy(livefileName,"./subtlety_live_out.txt");
strcpy(deadfileName, "./subtlety_dead_out.txt");
pLocationByType = sim_generate_location_param(pLocations, "BySubtlety", &compare_by_subtlety, &print_by_subtlety );
break;

case 3: 
/* type strategy */
strcpy(livefileName,"./strategy_live_out.txt");
strcpy(deadfileName, "./strategy_dead_out.txt");
pLocationByType = sim_generate_location_param(pLocations, "ByStrategy", &compare_by_strategy, &print_by_strategy );
break;

case 4: 
/* type level */
strcpy(livefileName,"./charm_live_out.txt");
strcpy(deadfileName, "./charm_dead_out.txt");
pLocationByType = sim_generate_location_param(pLocations, "ByCharm", &compare_by_charm, &print_by_charm );
break;

default:
pLocationByType = NULL;
break;

}

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
