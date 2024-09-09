#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "simulation.h"
#include "locations.h"
#include "heroes.h"
#include "heap.h"

void sim_print(void* data)
{


}

int compare_by_name(void* data1, void* data2)
{
  HeroNode* node1 = (HeroNode*)data1;
  HeroNode* node2 = (HeroNode*)data2;

 return strcmp(node2->name,node1->name);
   
}



Locations* sim_generate_location_param(Locations* pLocations, char* name, int (*compare)(void*, void*), void (*print)(void*) )
{
Heap* heap;
bool rc = false;

heap = heap_initialize(sizeof(LocationNode),name,compare,print);
//printf("sim_generate_location_param: heap initialiszed\n");

if(heap == NULL) return NULL;

int count = pLocations->arr->size;
for(int i = 0 ; i < count;i++)
{
   LocationNode* node = alist_get(pLocations->arr,i);
   if(node == NULL) return NULL;
   rc = heap_insert(heap,node);
   if(rc == false)
     return NULL;
}

count = heap_size(heap);

Locations* newLoc = locations_initialize();

if(newLoc == NULL)
return NULL;

for(int i = 0; i < count ; i++)
{
    LocationNode* node = heap_remove(heap);
    if(node == NULL)
    return NULL;
   rc = alist_add(newLoc->arr, node);
   if(rc == false)
   return NULL;
   free(node);
}
  rc = heap_destroy(heap); 
  if (rc == false)
  {
    alist_destroy(newLoc->arr);
    free(newLoc);
   return NULL;
  }

  return newLoc;
}





bool sim_createoutfile(Heap* heap, Locations* pLocations, char* livename, char* deadname)
{

FILE* fpLive;
FILE* fpDead;

fpLive = fopen(livename,"w");
fpDead = fopen(deadname,"w");

if(fpLive == NULL || fpDead == NULL)
return false;

//bool flag_file = sim_createoutfile(liveFileName, deadFileName, &fpLive, &fpDead);

int size = heap_size(heap);

//printf("sim_createoutfile: %d\n",size);
for(int i = 0 ; i < size; i++)
{
  HeroNode* player;
  player = heap_remove(heap);
  if(player->alive == true && player->level == 200)
  {
        char tempOut[256];
            sprintf(tempOut,"%s %2.2f %2.2f %2.2f %2.2f\n",player->name,player->attribute[0],player->attribute[1],player->attribute[2],player->attribute[3]);
            fputs(tempOut,fpLive); 

  }
  //else if(player->alive == false)
  else
  {
        char tempOut[256];
            LocationNode* location = alist_get(pLocations->arr,player->level);
            sprintf(tempOut,"%s %2.2f %2.2f %2.2f %2.2f %d %s\n",player->name,player->attribute[0],player->attribute[1],player->attribute[2],player->attribute[3],player->level, location->name);
            fputs(tempOut,fpDead); 
  }
}

fclose(fpLive);
fclose(fpDead);

return true;

}




bool _sim_challenge(LocationNode* loc, HeroNode* hero, int locationCount)
{

/* if any of palyer attribute is >= location rating player wins the location*/
if( (hero->attribute[Strength] >=  loc->rating[Power] ) ||
    (hero->attribute[Agility] >=  loc->rating[Subtlety] ) ||
    (hero->attribute[Intelligence] >=  loc->rating[Strategy] ) ||
    (hero->attribute[Charisma] >=  loc->rating[Charm] )
 )
{
   for(int i = 0 ; i < 4; i++)
   {
    if(i == hero->primaryAttribute)
        hero->attribute[i] += .35;
    else
        hero->attribute[i] += .25;   
    }    
    hero->level++;
    if(hero->level == 200)
    {
            hero->finish = true;
            hero->alive = true;
            return true;
    }
    else if(hero->level >= locationCount)
    {
            hero->finish = true;
            hero->alive = false;
            return false;
    }
  // won this game coninue as alive = true and finish = false*/  
    return true;
  }
  else
  {
    hero->finish = true;
    hero->alive = false;
    return false;
  } 

}





void* simulate(void* args)
{
Args* pArgs = (Args*)args;
CmnParam* cmnParam;

cmnParam = pArgs->cmnParam;
Heap* heap = cmnParam->heap;
HeroNode* player = pArgs->player;
Locations* pLocations = cmnParam->loc;

// while(player->recorded == false)
while(pArgs->_iscomplete == false)
{
  if(player->finish == false)
  {
          LocationNode* location = alist_get(pLocations->arr,player->level);
          
         sem_wait(&(location->sem_loc));
          _sim_challenge(location,player,pLocations->arr->size);
        sem_post(&(location->sem_loc));
         // printf("Completed _sim_challenge: Name:%s Level:%d\n",player->name,player->level);
          if( (player->alive == true && player->level == 200) || (player->alive == false))
          {
            pArgs->_iscomplete = true;
           // player->recorded = true;
          }
     
        }  
  }
//pArgs->_iscomplete = true;

}




Heap* sim_challenge(Heroes* pHeroes, Locations* pLocations,int poolSize)
{

if(pHeroes == NULL || pLocations == NULL || poolSize <= 0 )
return NULL;

Heap* heap;

heap = heap_initialize(sizeof(LocationNode),"LocationNode",&compare_by_name,&sim_print);


if(heap == NULL)
 return NULL;

//printf("heap initialized\n");
/* CmnParam would be used across all thread args */
CmnParam* cmnParam = malloc(sizeof(CmnParam));
cmnParam->heap = heap;
cmnParam->loc = pLocations;

//printf("cmnParam initialized\n");

int heroesTotal = pHeroes->arr->size;
int locationCount = pLocations->arr->size;
int heroComplete = 0;
int heroIndex = 0;


//printf("sim_challenge:heroesTotal %d, locationCount %d\n",heroesTotal,locationCount);
/* Ceate arraylist of Args pointer */
//ArrayList* arrArgs = alist_initialize(poolSize,sizeof(Args*),"Args");
Args** arrArgs = malloc(sizeof(Args*)*poolSize);

/* create array of thread id */
pthread_t* arr_pthreadId = malloc(sizeof(pthread_t)*poolSize);

if(arrArgs == NULL || arr_pthreadId == NULL)
 return NULL;

bool completionFlag = false;
/* Keep track of threadcount finished completion */
int completedThreadCount = 0;

/* Create a pool of threads and corresponding args and execute it */
  for(int i = 0; i < poolSize; i++)
  {
    Args* pArgs;
    pArgs = malloc(sizeof(Args));
    pArgs->cmnParam = cmnParam;
    pArgs->_iscomplete = false;
    pArgs->index = i;
    pArgs->player = alist_get(pHeroes->arr,i);
    
    //alist_add(arrArgs,pArgs);
    arrArgs[i] = pArgs;
    heroIndex++;
    pthread_create((arr_pthreadId +i), NULL, &simulate, pArgs);
  }
//printf("Created thread pool\n");

/* completionFlag is true when all playes processing is complete */
  while(completionFlag == false)
  {

    for(int i = 0; i < poolSize && completionFlag == false; i++)
    {
      /* Here all threads already created,  check completition status */
        Args* pArgs;
        //pArgs = alist_get(arrArgs,i);
        pArgs = arrArgs[i];
        if(pArgs == NULL)
    {
      printf("Args NULL Pointer from pool  \n");
      return NULL;
    }
        /*if thread processing is complete*/
        if((pArgs != NULL) && (pArgs->_iscomplete == true))
        {  
          pthread_t *ptrThread = (arr_pthreadId +i);
          int* result;
          /* Wait for thread to join and return processed value*/
          pthread_join(*ptrThread,(void**)&result);
          heap_insert(heap,pArgs->player);
          
          /* no memory allocated by  thread to free*/
           // free(result);
          /* one more player completed */
          heroComplete++;
          pArgs->_iscomplete = false;
         // printf("Completed Player complete %d, index:%d\n",heroComplete,heroIndex);
         /* check if more players to be processed */
          if (heroIndex < heroesTotal)
          {
            HeroNode* player = alist_get(pHeroes->arr,heroIndex);
            pArgs->player = player;
            pArgs->cmnParam = cmnParam;
            pArgs->_iscomplete = false;
            pArgs->index = heroIndex;
            heroIndex++;
            pthread_create((arr_pthreadId +i), NULL, &simulate, pArgs);
           // printf("Create New thread %d\n",heroIndex);
          }
          else
          {
            /* No more ops in array to be processed increase completed threadcount */
            completedThreadCount++;
           // printf("Completed Player %d, Thread: %d, Pool %d\n",heroComplete, completedThreadCount,poolSize);
            /* if all thread stopped means all processing complete*/
            if(completedThreadCount == poolSize)
              completionFlag = true;
          }
        }  
      }
  }
  /*alist_destroy(arrArgs);*/
  free(arr_pthreadId);
  free(arrArgs);
  free(cmnParam);

  // printf("Returning heap\n");
  return heap;


}

