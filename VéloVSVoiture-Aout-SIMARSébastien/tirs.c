#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "loadMap.h"
#include "player.h"
#include "tirs.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
tirsP r;
listetirsP t;

listetirsP  initialListeTirs()
{
	listetirsP t = malloc(sizeof(listeTirs));
	if (t == NULL)
	{
		exit(EXIT_FAILURE);
	}
	t->starList = NULL;
	t->endList = NULL;
	t->quantite = 0;
	return t;
}

tirsP createTirs(player p)
{
	int x = (p->pos.x);
	int y = ((p->pos.y)) + 1;
	tirsP new = malloc(sizeof(tirs));
	if (new == NULL)
	{
		exit(EXIT_FAILURE);
	}
	new->pos.x = x;
	new->pos.y = y;
	new->nextptr = NULL;
	new->prevptr = NULL;
	new->active = true;
	if (p->weapon ==false)
	{
		new->color=1; //color 1 =jaune (bal classique)
	}
	if (p->weapon == true)
	{
		new->color = 2; //color2 = bleu (bal ralentissseuse)
	}
	return new;
}

void insertionTirs(listetirsP t, tirsP base)
{
	tirsP new = malloc(sizeof(tirs));
	if (new == NULL)
	{
		exit(EXIT_FAILURE);
	}
	new = base;
	if (t->starList == NULL || t->endList == NULL)
	{
		t->endList = new;
		t->starList = new;
	}
	else
	{
		new->nextptr = t->starList;
		t->starList->prevptr = new;
		t->starList = new;
	}
	t->quantite += 1;
}

void suppressionTirs(listetirsP t, int test)
{
	test = 0;
	if (t->starList != NULL)
	{
		tirsP base = malloc(sizeof(tirs));
		tirsP deleate = malloc(sizeof(tirs));
		base = t->starList;
		while (base != NULL)
		{
			if (base->active == test)
			{
				deleate = base;
				base = base->nextptr;
				if (t->starList == deleate && t->endList == deleate)
				{
					t->endList = NULL;
					t->starList = NULL;
				}
				else if (t->starList != deleate && t->endList == deleate)
				{
					t->endList = deleate->prevptr;
					t->endList->nextptr = NULL;
				}
				else if (t->starList == deleate && t->endList != deleate)
				{
					t->starList = deleate->nextptr;
					t->starList->prevptr = NULL;
				}
				else
				{
					deleate->nextptr->prevptr = deleate->prevptr;
					deleate->prevptr->nextptr = deleate->nextptr;
				}
				free(deleate);
				t->quantite--;
			}
			else
			{
				base = base->nextptr;
			}
		}
		free(base);
	}
}

void tirer(player p, listetirsP t)
{
	tirsP new = createTirs(p);
	insertionTirs(t, new);
}

tirsP createTirs8(int x,int y)
{
	tirsP new = malloc(sizeof(tirs));
	if (new == NULL)
	{
		exit(EXIT_FAILURE);
	} 
	new->pos.x = x;
	new->pos.y = y;
	new->nextptr = NULL;
	new->prevptr = NULL;
	new->active = true;
	new->color=1; //color 1 =jaune (bal classique)
	return new;
}

tirsP createTirs9(int x,int y)
{
	tirsP new = malloc(sizeof(tirs));
	if (new == NULL)
	{
		exit(EXIT_FAILURE);
	} 
	new->pos.x = x;
	new->pos.y = y;
	new->nextptr = NULL;
	new->prevptr = NULL;
	new->active = true;
	new->color=2; //color 2 = bleu (freeze)
	return new;
}

listetirsP loadTirs(int mX, int mY)			// fonction qui va charger à partir de la carte les points  destinés à devenir la ligne de la carte save .
{	
    t = initialListeTirs();
	for (int j = 0; j < (mX); ++j)
	{
		for (int i = 0; i < (mY); ++i)
		{
			if(*(*(map + j) + i) == '8')
			{
                tirsP new = createTirs8(j,i);
                insertionTirs (t,new);
            }
			if(*(*(map + j) + i) == '9')
			{
                tirsP new = createTirs9(j,i);
                insertionTirs (t,new);
			}	    
		}	
    }
return t;
}

