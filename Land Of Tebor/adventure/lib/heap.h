#ifndef __heap__
#define __heap__

#include"array_list.h"
#include<stdbool.h>



typedef struct _Heap {
ArrayList* list;
int (*compare)(void*, void*);
void (*print)(void*);
} Heap;

Heap* heap_initialize(int itemSize, char* type, int (*compare)(void*, void*), void (*print)(void*));

bool heap_insert(Heap* pHeap, void* data);

void* heap_remove(Heap* pHeap);

void* heap_peek(Heap* pHeap);

bool heap_contains(Heap* pHeap, void* data);

int heap_size(Heap* pHeap);


bool _heapify(Heap* pHeap, int index);

bool _heapify_up(Heap* pHeap, int index);

void heap_print_at_index(Heap* pHeap, int index);
void heap_print_all(Heap* pHeap);

void* heap_get_at(Heap* heap, int index);

int heap_compare(Heap* pHeap, int firstIndex, int secondIndex);

bool heap_destroy(Heap* pHeap);
#endif