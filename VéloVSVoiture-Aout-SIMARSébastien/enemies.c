#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "loadMap.h"
#include "enemies.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
enemy q;
listeEn e;

listeEn initialListeEnemies()//initialise la liste d'ennemis
{
	listeEn e = malloc(sizeof(listeEnemies));
	if (e == NULL)
	{
		exit(EXIT_FAILURE);
	}
	e->starList = NULL;
	e->endList = NULL;
	e->quantite = 0;
	return e;
}

enemy createEnemy(int *maxY)//fonction qui crée les ennemis aléatoirement en haut de la map 
{
	int random_indexnblife = rand() %5;
	int numeronblife[]={1,1,1,1,3}; //le niveau des ennemis est généré aléatoirement 
	int nb_point_vie= numeronblife[random_indexnblife];
	int random_index = rand() %8;
	int numeros[]={9,10,15,16,21,22,27,28}; //ligne d'apparition des enemis en x
	int y= numeros[random_index];
	enemy new = malloc(sizeof(enemies));
	if (new == NULL)
	{
		exit(EXIT_FAILURE);
	} 
	new->life= nb_point_vie;
	new->pos.x = 1;
	new->pos.y = y;
	new->nextptr = NULL;
	new->prevptr = NULL;
	new->active = 1;
	return new;
}

void insertionEnemies(listeEn e, enemy base)
{
	enemy new = malloc(sizeof(enemies));
	if (new == NULL)
	{
		exit(EXIT_FAILURE);
	}
	new = base;
	if (e->starList == NULL || e->endList == NULL)
	{
		e->endList= new;
		e->starList = new;
	}
	else
	{
		new->nextptr = e->starList;
		e->starList->prevptr = new;
		e->starList = new;
	}
	e->quantite += 1;
}

void suppressionEnemies(listeEn e, int test)
{
	test = 0;
	if (e->starList != NULL)
	{
		enemy base = malloc(sizeof(enemies));
		enemy deleate = malloc(sizeof(enemies));
		if (base == NULL)
		{
			exit(EXIT_FAILURE);
		}
		base = e->starList;
		while (base != NULL)
		{
			if (base->active == test)
			{
				deleate = base;
				base = base->nextptr;
				if (e->starList == deleate && e->endList == deleate)
				{
					e->starList = NULL;
					e->endList = NULL;
				}
				else if (e->starList != deleate && e->endList == deleate)
				{
					e->endList = deleate->prevptr;
					e->endList->nextptr = NULL;
				}
				else if (e->starList == deleate && e->endList != deleate)
				{
					e->starList  = deleate->nextptr;
					e->starList->prevptr = NULL;
				}
				else
				{
					deleate->nextptr->prevptr = deleate->prevptr;
					deleate->prevptr->nextptr = deleate->nextptr;
				}
				free(deleate);
				e->quantite--;
			}
			else
			{
				base = base->nextptr;
			}
		}
	free(base);
	}
}

enemy createEnemy7(int x,int y)// créer tous ces types d'ennemis me sert selon ce qui est enregistré sur la carte save (détaillé dans .h)
{
	enemy new = malloc(sizeof(enemies));
	if (new == NULL)
	{
		exit(EXIT_FAILURE);
	} 
	new->life= 1;
	new->pos.x = x;
	new->pos.y = y;
	new->nextptr = NULL;
	new->prevptr = NULL;
	new->active = 1;
	return new;
}

enemy createEnemyg(int x,int y)
{
	enemy new = malloc(sizeof(enemies));
	if (new == NULL)
	{
		exit(EXIT_FAILURE);
	} 
	new->life= 2;
	new->pos.x = x;
	new->pos.y = y;
	new->nextptr = NULL;
	new->prevptr = NULL;
	new->active = 1;
	return new;
}

enemy createEnemyh(int x,int y)
{
	enemy new = malloc(sizeof(enemies));
	if (new == NULL)
	{
		exit(EXIT_FAILURE);
	} 
	new->life= 3;
	new->pos.x = x;
	new->pos.y = y;
	new->nextptr = NULL;
	new->prevptr = NULL;
	new->active = 1;
	return new;
}

enemy createEnemyi(int x,int y)
{
	enemy new = malloc(sizeof(enemies));
	if (new == NULL)
	{
		exit(EXIT_FAILURE);
	} 
	new->life= 1;
	new->pos.x = x;
	new->pos.y = y;
	new->nextptr = NULL;
	new->prevptr = NULL;
	new->active = 3;
	return new;
}

enemy createEnemyj(int x,int y)
{
	enemy new = malloc(sizeof(enemies));
	if (new == NULL)
	{
		exit(EXIT_FAILURE);
	} 
	new->life= 2;
	new->pos.x = x;
	new->pos.y = y;
	new->nextptr = NULL;
	new->prevptr = NULL;
	new->active = 3;
	return new;
}

enemy createEnemyk(int x,int y)
{
	enemy new = malloc(sizeof(enemies));
	if (new == NULL)
	{
		exit(EXIT_FAILURE);
	} 
	new->life= 3;
	new->pos.x = x;
	new->pos.y = y;
	new->nextptr = NULL;
	new->prevptr = NULL;
	new->active = 3;
	return new;
}

listeEn loadEnnemis(int mX, int mY)	// fonction qui va charger les ennemis apd de la carte save 
									//et qui va ensuite les insérer dans la liste chainée selon ces valeurs (vie/freez/pos) .
{	
    e = initialListeEnemies();
	for (int j = 0; j < (mX); ++j)
	{
		for (int i = 0; i < (mY); ++i)
		{
			if(*(*(map + j) + i) == '7')
			{
                enemy new = createEnemy7(j,i);
                insertionEnemies (e,new);
            }
			if(*(*(map + j) + i) == 'g')
			{
                enemy new = createEnemyg(j,i);
                insertionEnemies (e,new);
            }
			if(*(*(map + j) + i) == 'h')
			{
                enemy new = createEnemyh(j,i);
                insertionEnemies (e,new);
            }
			if(*(*(map + j) + i) == 'i')
			{
                enemy new = createEnemyi(j,i);
                insertionEnemies (e,new);
            }
			if(*(*(map + j) + i) == 'j')
			{
                enemy new = createEnemyj(j,i);
                insertionEnemies (e,new);
            }
			if(*(*(map + j) + i) == 'k')
			{
                enemy new = createEnemyk(j,i);
                insertionEnemies (e,new);
            }
		}	
    }
return e;
}

