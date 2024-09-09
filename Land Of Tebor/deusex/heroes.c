#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heroes.h"


#define HEROES_INITIAL_SIZE 100

Heroes* heroes_initialize()
{
Heroes* pHeroes = NULL;

pHeroes = malloc(sizeof(Heroes));

if(pHeroes == NULL)
return NULL;

pHeroes->arr = alist_initialize(HEROES_INITIAL_SIZE,sizeof(HeroNode),"Heroes");

if(pHeroes->arr == NULL)
{
  free (pHeroes);
  return NULL;
}

return pHeroes;

}

bool heroes_resetHero(HeroNode* player)
{
  if(player == NULL)
  return false;

player->level = 0;
player->finish = false;
player->alive = true;
//player->heroesTotal = false;

return true;
}

bool heroes_resetHeroes(Heroes* pHeroes)
{

if(pHeroes == NULL)
return false;
int size = pHeroes->arr->size;
for(int i = 0; i < size; i++)
{
HeroNode* player = alist_get(pHeroes->arr,i);
if(player == NULL)
return false;

heroes_resetHero(player);
}

return true;


}


bool heroes_createHero(Heroes* pHeroes, char* name, char* heroClass, char* attributes)
{
bool returnStatus = false;

if(pHeroes == NULL || name == NULL || heroClass == NULL || attributes == NULL)
return returnStatus;

HeroNode* player = malloc(sizeof(HeroNode));
if(player == NULL) return false;

heroes_resetHero(player);

size_t  length = strlen(name);
player->name = malloc(length+1);
strcpy(player->name, name);

length = strlen(heroClass);
player->heroClass = malloc(length+1);
strcpy(player->heroClass, heroClass);

//printf("Player: Name: %s, Class: %s\n",player->name,player->heroClass);

char* token;
char *temp;
int count = 0;
long tempVal = 0;
token = strtok(attributes,"- ");
while(token!= NULL && count < 4)
{
   tempVal = strtol(token, &temp, 10);
   player->attribute[count] = (int)tempVal;
    token = strtok(NULL,"- ");
    count++;
}

if(count != 4)
return returnStatus;


/* Calculte primaryAttribute */
count = 0;
int largest = player->attribute[count];
int primaryIndex = 0;

count++;

while(count < 4)
{
  if(largest < player->attribute[count])
  {
  primaryIndex = count;
  largest = player->attribute[count];
  }
  count++;
}

player->primaryAttribute = primaryIndex;

returnStatus = alist_add(pHeroes->arr,player);

return returnStatus;
}




bool  heroes_load(Heroes* pHeroes, char* filename)
{

FILE* pFile = NULL;
pFile = fopen(filename,"r");

if(pFile == NULL)  return NULL;


char line[256]; 
char heroLines[3][256];
int rowCount = 0;
size_t count = 256;
size_t length = 0;



while(fgets(line,count,pFile) != NULL)
{
     int len = strlen(line);
     line[len -1] = '\0';
        switch(rowCount)
        {
            case 0:
            strcpy(heroLines[0],line);
            break;
            case 1:
            strcpy(heroLines[1],line);
            break;
            case 2:
            strcpy(heroLines[2],line);
            break;
        
    }
    rowCount++;
    if(rowCount == 3)
    {
         rowCount = 0;
         heroes_createHero(pHeroes, heroLines[0], heroLines[1], heroLines[2]);
    }

}

if(rowCount !=0)
  printf("File %s is corrupt \n");

return true;
}





