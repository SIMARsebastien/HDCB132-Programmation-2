#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "loadMap.h"
#include "midleline.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
ML k;
listeML m;

listeML initialListeMLS()
{
	listeML m = malloc(sizeof(listeMLS));
	if (m == NULL)
	{
		exit(EXIT_FAILURE);
	}
	m->starList = NULL;
	m->endList = NULL;
	m->quantite = 1;
	return m;
}

ML createML(int *maxY)
{
	ML new = malloc(sizeof(MLS));
	int y = 19; 
	if (new == NULL)
	{
		exit(EXIT_FAILURE);
	} 
	new->vie = 1;
	new->pos.x = 0;
	new->pos.y = y;
	new->nextptr = NULL;
	new->prevptr = NULL;
	new->active = true;
	return new;
}

void insertionMLS(listeML m, ML base)
{
	ML new = malloc(sizeof(MLS));
	if (new == NULL)
	{
		exit(EXIT_FAILURE);
	}
	new = base;
	if (m->starList == NULL || m->endList == NULL)
	{
		m->endList= new;
		m->starList = new;
	}
	else
	{
		new->nextptr = m->starList;
		m->starList->prevptr = new;
		m->starList = new;
	}
	m->quantite += 1;
}

void suppressionMLS(listeML m, bool test)
{
	test = false;
	if (m->starList != NULL)
	{
		ML base = malloc(sizeof(MLS));
		if (base == NULL)
		{
			exit(EXIT_FAILURE);
		}
		base = m->starList;
		while (base != NULL)
		{
			if (base->active == test)
			{
				ML deleate = malloc(sizeof(MLS));
				deleate = base;
				base = base->nextptr;
				if (m->starList == deleate && m->endList == deleate)
				{
					m->starList = NULL;
					m->endList = NULL;
				}
				else if (m->starList != deleate && m->endList == deleate)
				{
					m->endList = deleate->prevptr;
					m->endList->nextptr = NULL;
				}
				else if (m->starList == deleate && m->endList != deleate)
				{
					m->starList  = deleate->nextptr;
					m->starList->prevptr = NULL;
				}
				else
				{
					deleate->nextptr->prevptr = deleate->prevptr;
					deleate->prevptr->nextptr = deleate->nextptr;
				}
				free(deleate);
				m->quantite--;
			}
			else
			{
				base = base->nextptr;
			}
		}
	}
}

