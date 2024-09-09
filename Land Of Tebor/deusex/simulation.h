#ifndef __SIMULATIONH__
#define __SIMULATIONH__

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "heap.h"
#include "locations.h"
#include "heroes.h"

/* Param common across all threads */
typedef struct _CmnParam
{
 Locations* loc; 
 Heap* heap;
} CmnParam;

/* Args to be passed to thread */

typedef struct __Args{
HeroNode* player;
CmnParam* cmnParam;
int index;
bool _iscomplete;

} Args;

Locations* sim_generate_location_param(Locations* pLocations, char* name, int (*compare)(void*, void*), void (*print)(void*) );


void* simulate(void* pArgs);

bool sim_createoutfile(Heap* heap, Locations* loc, char* livename, char* deadname);

bool _sim_challenge(LocationNode* loc, HeroNode* hero, int locationCount);


Heap* sim_challenge(Heroes* pHeroes, Locations* pLocations,int poolSize);







#endif