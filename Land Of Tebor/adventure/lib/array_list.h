#ifndef __array_list__
#define __array_list__


#include<stdbool.h>



typedef struct _AList {
void** arr;
int size;
int maxSize;
int itemSize;
char* type;
} ArrayList;

ArrayList* alist_initialize(int maxSize, int itemSize, char* type);

bool alist_add(ArrayList* arrList, void* data);

bool alist_add_at(ArrayList* arrList, int index, void* data);

void alist_clear(ArrayList* arrList);

void* alist_get(ArrayList* arrList, int index);

int alist_index_of(ArrayList* arrList, void* data);

void* alist_remove(ArrayList* arrList, int index);

bool alist_destroy(ArrayList* arrlist);

bool alist_resize(ArrayList* arrlist);

int alist_size(ArrayList* arrList);

bool alist_add_at_end(ArrayList* arrList,  void* data);

bool alist_swap(ArrayList* arrList, int firstIndex, int secondIndex);

bool alist_decreaseSize(ArrayList* arrList);
#endif