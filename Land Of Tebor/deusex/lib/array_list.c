#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <stdbool.h>

/* #define __USE_C99_MATH */

#include "array_list.h"


ArrayList* alist_initialize(int maxSize, int itemSize, char* type)
{
ArrayList*  arrList;

if(type == NULL || maxSize <= 0 || itemSize <= 0 ) return NULL;

arrList = malloc(sizeof (ArrayList));

if(arrList == NULL) return NULL;

arrList->maxSize = maxSize;
arrList->itemSize= itemSize;
arrList->size = 0;



arrList->arr = malloc(sizeof *(arrList->arr) * maxSize);

/*arrList->arr = calloc(sizeof *(arrList->arr) , maxSize);*/

if(arrList->arr ==NULL)
{
   free(arrList);
   return NULL;
}

/* allocate one etra space to handle string */
arrList->type= (char*)malloc(sizeof(strlen(type) + 1)*sizeof(char*));
if(arrList->type == NULL)
{
  free(arrList);
  free(arrList->arr);
  return NULL;

}

strcpy(arrList->type, type);


return arrList;

}

bool alist_add(ArrayList* arrList, void* data)
{
   void* newData;
   if(arrList->size == arrList->maxSize)
   {
      if(alist_resize(arrList) == false)
        return false;
   }

/* Allocate memory for data to be stored in ArrayList*/
   newData = (void*)malloc(arrList->itemSize);

   memcpy(newData,data,arrList->itemSize);
   arrList->arr[arrList->size] = newData;
   arrList->size += 1;

   return true;


}


bool alist_add_at(ArrayList* arrList, int index, void* data)
{
  void* newData;

  if(arrList == NULL  || index < 0 || index > arrList->size)  return false;

/* First check if array list has space to add new element */
   if(arrList->size == arrList->maxSize)
   {
      if(alist_resize(arrList) == false)
        return false;
   }

/* if new position is at end no shifting required*/
if(arrList->size != index)
{
/* move the elements starting from index position to size - 1*/
for(int i = arrList->size ; i > index; i--){
   arrList->arr[i] = arrList->arr[i-1];
}
}


newData = malloc(arrList->itemSize);
   memcpy(newData,data,arrList->itemSize);
    arrList->arr[index] = newData;

  arrList->size += 1;

return true;

}

void alist_clear(ArrayList* arrList)
{
  if(arrList == NULL  ||  arrList->size == 0)  return;

  for(int i = 0 ; i <  arrList->size ; i++)
  {
    if(arrList->arr[i] != NULL)
    {
      free(arrList->arr[i]);
      arrList->arr[i] = NULL;
    }
  }
  arrList->size = 0;
}


void* alist_get(ArrayList* arrList, int index)
{

    if(arrList == NULL  || index < 0 || index >= arrList->size)  return NULL;

    return arrList->arr[index];
}

int alist_index_of(ArrayList* arrList, void* data)
{
   int index = -1;

    if(arrList == NULL  || data == NULL || arrList->size == 0)  return index;


    for(int i = 0 ;i < arrList->size && index == -1; i++)
    {

       if ( memcmp(arrList->arr[i],data,arrList->itemSize) == 0)
        index = i;
    }
    return index;
}






void* alist_remove(ArrayList* arrList, int index){
  void* tempData = NULL;
  if(arrList == NULL  || index < 0 || index >= arrList->size)  return NULL;

  tempData = arrList->arr[index];

  for(int i = index; i < arrList->size; i++){
     arrList->arr[i] = arrList->arr[i + 1];
  }
arrList->size -= 1;

return tempData;
}

bool alist_destroy(ArrayList* arrList){
  if(arrList == NULL) return false;

  alist_clear(arrList);
  if(arrList->type != NULL)
    free(arrList->type);
  if(arrList->arr != NULL)
    free(arrList->arr);
  
  arrList->maxSize = 0;

  return true;

}





bool alist_resize(ArrayList* arrList){
  void** newPtr;

  if(arrList == NULL) return false;

/* grow memorysize by 2 */
  int newSize = arrList->maxSize * 2;

  newPtr = malloc(sizeof *(arrList->arr) * newSize);
  if(newPtr == NULL) return false;

/* copy old memory content in new */
for(int i = 0; i < arrList->size; i++)
{
  newPtr[i] = arrList->arr[i];
  arrList->arr[i] = NULL;
}
/* free old memory */
free(arrList->arr);

/* point to new memory location and set new size*/
arrList->arr = newPtr;
  arrList->maxSize = newSize;

   return true;
}

int alist_size(ArrayList* arrList)
{
 if(arrList == NULL) return -1;

 return arrList->size;
 
}

bool alist_add_at_end(ArrayList* arrList,  void* data)
{
  void* newData;
  int index;

  if(arrList == NULL || data == NULL)  return false;

/* First check if array list has space to add new element */
   if(arrList->size == arrList->maxSize)
   {
      if(alist_resize(arrList) == false)
        return false;
   }


newData = malloc(arrList->itemSize);
if(newData == NULL)
 return false;
   memcpy(newData,data,arrList->itemSize);
/* adding at end so index has to be equal to size */
   index = arrList->size;
    arrList->arr[index] = newData;

  arrList->size += 1;

return true;

}


bool alist_swap(ArrayList* arrList, int firstIndex, int secondIndex)
{

  void* data;
  if(arrList == NULL  || ( firstIndex < 0 || firstIndex >= arrList->size ) || ( secondIndex < 0 || secondIndex >= arrList->size ))  return false;


if(firstIndex == secondIndex ) return true;

/* swap the data pointer */
   data = arrList->arr[firstIndex];
   arrList->arr[firstIndex] = arrList->arr[secondIndex];
   arrList->arr[secondIndex] = data;
    
    
   return true;

}

bool alist_decreaseSize(ArrayList* arrList)
{
 if(arrList == NULL || arrList->size == 0) return false;
 
 arrList->size -= 1;

 return true;
}