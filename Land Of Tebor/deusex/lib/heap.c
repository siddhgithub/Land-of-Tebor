#include<stdio.h>
#include<stdlib.h>
#include"heap.h"

#define HEAP_ALIST_INITIAL_SIZE 100



Heap* heap_initialize(int itemSize, char* type, int (*compare)(void*, void*), void (*print)(void*))
{
Heap* pHeap;
ArrayList* pList;
/* Check for invalid input parameters */
if(itemSize <= 0, type == NULL || compare == NULL || print == NULL) return NULL;

pHeap = malloc(sizeof (Heap));
if(pHeap == NULL) return NULL;

pList = alist_initialize(HEAP_ALIST_INITIAL_SIZE,itemSize,type);

/* failed to initialise ArrayList */
if(pList == NULL){
free(pHeap);
return NULL;
}

pHeap->list = pList;
pHeap->compare = compare;
pHeap->print = print;

return pHeap;
}



void* heap_peek(Heap* pHeap)
{
/* Check for invalid input parameters */
if( pHeap == NULL) 
return NULL;
return alist_get(pHeap->list,0);
}

bool heap_contains(Heap* pHeap, void* data)
{
int index;
/* Check for invalid input parameters */
if( pHeap == NULL || data == NULL) 
return NULL;
index = alist_index_of(pHeap->list,data);
return index >= 0 ? true:false;
}

int heap_size(Heap* pHeap)
{
    /* Check for invalid input parameters */
if( pHeap == NULL ) 
return -1;

return alist_size(pHeap->list);

}

bool heap_insert(Heap* pHeap, void* data)
{
bool flag;
/* Check for invalid input parameters */
if( pHeap == NULL || data == NULL) 
return false;

flag = alist_add_at_end(pHeap->list, data);
if(flag == false) return flag;

int size = alist_size(pHeap->list);

return _heapify_up(pHeap, size - 1);

}


/* used to insert element at end of array list and push it upward at right index
*/
bool _heapify_up(Heap* pHeap, int index)
{
bool flag;    
if( pHeap == NULL || index < 0) 
return false;

/* element is already at head nothing to do */
if(index == 0)  return true;

int parentIndex = (int)(index - 1)/2;
void* parentData = alist_get(pHeap->list,parentIndex );
void* data = alist_get(pHeap->list,index );

if(parentData == NULL || data == NULL) return false;

/* if parentData is less then child no adjustment required */
if (pHeap->compare(data, parentData) <= 0) return true;

flag = alist_swap(pHeap->list, parentIndex, index);
if(flag == false) return false;
/* Make recursive call */
return _heapify_up(pHeap,parentIndex);
}

void heap_print_at_index(Heap* pHeap, int index)
{
if( pHeap == NULL)
{
    printf("\nheap_print_at_index: invalid input\n");
    return;
}

void* data = alist_get(pHeap->list,index);
if(data == NULL)
{
    
    printf("\nheap_print_at_index: invalid input\n");
    return;
}

pHeap->print(data);

}

void heap_print_all(Heap* pHeap)
{
if( pHeap == NULL)
{
    printf("\nheap_print_all: invalid input\n");
    return;
}

int size = alist_size(pHeap->list);
for(int i = 0 ; i < size; i++)
  heap_print_at_index(pHeap,i);

}


void* heap_remove(Heap* pHeap)
{
bool flag;
void* data;
int size;
/* Check for invalid input parameters */
if( pHeap == NULL ) 
return NULL;

size = heap_size(pHeap);

if(size <= 0)
return NULL;

data =  alist_get(pHeap->list, 0);
size = heap_size(pHeap);


/* if size is 1 no need to adjust heap */
if(size == 1)
{
alist_decreaseSize(pHeap->list);
return data;
}

flag = alist_swap(pHeap->list,0, (size-1));
if(flag == false) return NULL;

flag = _heapify(pHeap, 0);
if(flag == false) return NULL;
else
{
 alist_decreaseSize(pHeap->list); 
 return data;
}
}





/* used to remove element at given index
*/
bool _heapify(Heap* pHeap, int index)
{
/* Check for invalid input parameters */
if( pHeap == NULL || index < 0) 
return false;

int size = alist_size(pHeap->list);


int topIndex = index;
int leftIndex =  2*index + 1;
int rightIndex = 2*(index + 1); 

/*if(leftIndex >= size  || rightIndex >= size)
return true; */

if( leftIndex < (size -1 ))
{
  if (heap_compare(pHeap,leftIndex,topIndex) > 0)
    topIndex = leftIndex;
}

if(rightIndex < (size -1) )
{
  if (heap_compare(pHeap,rightIndex,topIndex) > 0)
    topIndex = rightIndex;
}

if(topIndex == index)
  return true;

int flag = alist_swap(pHeap->list,index, topIndex);

if(flag == false)
  return false;

return  _heapify(pHeap,topIndex);
  
}


int heap_compare(Heap* pHeap, int firstIndex, int secondIndex)
{
 int value; 
if( pHeap == NULL || firstIndex < 0 || secondIndex < 0) 
return -1;

void* firstData = alist_get(pHeap->list,firstIndex);
void* secondData = alist_get(pHeap->list,secondIndex);
 value = pHeap->compare(firstData,secondData);
 return value;
}

bool heap_destroy(Heap* pHeap)
{
if(pHeap == NULL)
 return false;

 if(pHeap->list != NULL)
 alist_destroy(pHeap->list);

free(pHeap);

return true;
}
