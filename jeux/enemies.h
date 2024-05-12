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
	int life;
	struct positionE pos;
	int active;
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
void suppressionEnemies(listeEn e, int test);
extern enemy q;
extern listeEn e;
enemy createEnemy7(int x,int y);//ennemis non freez et 1hp
enemy createEnemyg(int x,int y);//non freez 2hp
enemy createEnemyh(int x,int y);//non freez 3hp
enemy createEnemyi(int x,int y);//freez 1hp
enemy createEnemyj(int x,int y);//freez 2hp
enemy createEnemyk(int x,int y);//ennemis freez avec 3pv
listeEn loadEnnemis(int mX, int mY);//charge les enemis de la carte de sauvegarde
#endif
