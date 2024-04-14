#ifndef _ENEMIES_H_
#define _ENEMIES_H_


#include <stdbool.h>

struct positionE
{
	int x;
	int y;
};
typedef struct enemies enemies;
struct enemies
{
	int vie;
	struct positionE pos;
	bool active;
	struct enemies *prevptr;
	struct enemies *nextptr;
};

typedef struct listeEnemies listeEnemies;
struct listeEnemies
{
	
	int quantite;
	struct enemies *starList;
	struct enemies *endList;
	
};

typedef struct enemies *enemy; 
typedef struct listeEnemies *listeEn;
enemy createEnemy(int *maxY);
listeEn  initialListeEnemies();//attention pe enlever le e
void insertionEnemies(listeEn e, enemy q);
void suppressionEnemies(listeEn e, bool test);
extern enemy q;
extern listeEn e;

#endif
