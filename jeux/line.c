#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "loadMap.h"
#include "line.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
line l; //premier élément de la ligne
listeLi li; // la liste de ligne 

listeLi initialListeLine()//initiallise la liste pour la ligne
{
	listeLi li = malloc(sizeof(listeLines));
	if (li == NULL)
	{
		exit(EXIT_FAILURE);
	}
	li->starList = NULL;
	li->endList = NULL;
	li->quantite = 0;
	return li;
}

line createLine(int x, int y)
{
	line new = malloc(sizeof(lines)); 
	if (new == NULL)
	{
		exit(EXIT_FAILURE);
	} 
	new->pos.x = x;
	new->pos.y = y;
	new->nextptr = NULL;
	new->prevptr = NULL;

	return new;
}

void insertionLines(listeLi li, line base)
{
	line new = malloc(sizeof(lines));
	if (new == NULL)
	{
		exit(EXIT_FAILURE);
	}
	new = base;
	if (li->starList == NULL || li->endList == NULL)
	{
		li->endList= new;
		li->starList = new;
	}
	else
	{
		new->nextptr = li->starList;
		li->starList->prevptr = new;
		li->starList = new;
	}
	li->quantite += 1;
}

listeLi loadLine(int mX, int mY)			// fonction qui va charger à partir de la carte les points  destinés à devenir la ligne.
{	
    li = initialListeLine();
	for (int j = 0; j < (mX); ++j)
	{
		for (int i = 0; i < (mY); ++i)
		{
			if(*(*(map + j) + i) == '3')
			{
                line new = createLine(j,i);
                insertionLines (li,new);
            }
        }
    }
return li;
}