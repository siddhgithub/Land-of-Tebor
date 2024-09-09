#ifndef __HEROESH__
#define __HEROESH__

#include "array_list.h"

typedef enum {
Strength,
Agility,
Intelligence,
Charisma
}HERO_Attribute;


typedef struct {
char* name;
char* heroClass;
float attribute[4];
int level;
int primaryAttribute;
//int location;
bool finish;
bool alive;
//bool recorded;
}HeroNode;


typedef struct {

ArrayList* arr;

} Heroes;

Heroes* heroes_initialize();


bool heroes_createHero(Heroes* pHeroes, char* name, char* heroClass, char* attributes);

bool  heroes_load(Heroes* pHeroes, char* filename);

bool heroes_resetHeroes(Heroes* pHeroes);

bool heroes_resetHero(HeroNode* player);


#endif