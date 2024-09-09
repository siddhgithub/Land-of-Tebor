#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "locations.h"

bool locations_destroy(Locations* pLocations)
{
bool returnstatus = false;
if(pLocations == NULL) return returnstatus;

if(pLocations->arr != NULL)
 returnstatus = alist_destroy(pLocations->arr);

 free(pLocations);

 return returnstatus;

}


Locations* locations_initialize()
{
Locations* pLocations = NULL;

pLocations = malloc(sizeof(Locations));

if(pLocations == NULL) return NULL;

pLocations->arr = alist_initialize(100,sizeof(LocationNode),"Locations");

if(pLocations->arr == NULL)
{
  free(pLocations);
  return NULL;
}
return pLocations;

}


bool locations_createLocation(Locations* pLocations, char* name, char* ratings)
{
bool returnStatus = false;

if(pLocations == NULL || name == NULL || ratings == NULL)
return returnStatus;

LocationNode* location = malloc(sizeof(LocationNode));

if(location == NULL) return returnStatus;


size_t  length = strlen(name);
location->name = malloc(length+1);
strcpy(location->name, name);

sem_init(&location->sem_loc, 0, 1);

char* token;
char *temp;
int count = 0;
long tempVal = 0;
token = strtok(ratings,"- ");

while(token!= NULL && count < 5)
{
  tempVal = strtol(token, &temp, 10);
  if(count == 0)
    location->level = (int)tempVal;
  else
  {
   /* firsst token is of level so index is count -1 */
   location->rating[count -1] = (int)tempVal;
  } 
    token = strtok(NULL,"- ");
    count++;
}

if(count != 5)
return returnStatus;


returnStatus = alist_add(pLocations->arr,location);

return returnStatus;
}




bool  locations_load(Locations* pLocations, char* filename)
{
bool returnStatus = false;
FILE* pFile = NULL;

if((pLocations == NULL) || (filename == NULL))
  return returnStatus;

pFile = fopen(filename,"r");

if(pFile == NULL)  return returnStatus;


char line[256]; 
char locationLines[2][256];
int rowCount = 0;
size_t count = 256;
size_t length = 0;

returnStatus = true;

while((fgets(line,count,pFile) != NULL) && (returnStatus == true))
  {
      int len = strlen(line);
      /* remove new line character from last location*/
      line[len -1] = '\0';
      switch(rowCount)
      {
            case 0:
            strcpy(locationLines[0],line);
            break;
            case 1:
            strcpy(locationLines[1],line);
            break;  
      }
      rowCount++;
      if(rowCount == 2)
      {
         rowCount = 0;
         returnStatus = locations_createLocation(pLocations, locationLines[0], locationLines[1]);
      }

  }

if((rowCount !=0) || (returnStatus == false))
{
  printf("File %s is corrupt \n");
  return false;
}
return true;
}





