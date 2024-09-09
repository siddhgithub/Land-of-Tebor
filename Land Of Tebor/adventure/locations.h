#ifndef __LOCATIONSH__
#define __LOCATIONSH__

#include <stdbool.h>
#include "array_list.h"
#include <semaphore.h>

typedef enum {
Power,
Subtlety,
Strategy,
Charm
}LocationAttribute;



typedef struct {
char* name;
int level;
sem_t sem_loc;
LocationAttribute rating[4];

}LocationNode;


typedef struct {

ArrayList* arr;

} Locations;

Locations* locations_initialize();


bool locations_createLocation(Locations* pLocations, char* name,  char* ratings);

bool  locations_load(Locations* pLocations, char* filename);


#endif