#ifndef __ADVENTURETYPEH__
#define __ADVENTURETYPEH__

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "heap.h"
#include "locations.h"
#include "heroes.h"

void sim_print(void*);



int compare_by_level(void* data1, void* data2);
int compare_by_power(void* data1, void* data2);
int compare_by_subtlety(void* data1, void* data2);
int compare_by_strategy(void* data1, void* data2);
int compare_by_charm(void* data1, void* data2);

void print_by_level(void* data);
void print_by_power(void* data);
void print_by_subtlety(void* data);
void print_by_strategy(void* data);
void print_by_charm(void* data);



bool adventure_startgame(int gametype, int threadCount);






#endif
