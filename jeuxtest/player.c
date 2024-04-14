#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "loadMap.h"
#include "player.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
player p;

player createPlayer(int *maxX, int *maxY)
{
	player p;

	int x = 0, y = 0;

	for (int i = 0; i < *maxX; ++i)
	{
		for (int j = 0; j < *maxY; ++j)
		{
			if(*(*(map + i) + j) == 'X')
			{
				x = i;
				y = j;
			}
		}
	}

	p = malloc(sizeof(player));
	p->vie = 3;
	p->pos.x = x;
	p->pos.y = y;

	return p;
}

void moveLeft(player p)//la fonction va vérifier si on peut se déplacer vers la gauche et le faire le cas échéant
{
	int x = 0, y = 0;
	x = p->pos.x;
	y = p->pos.y - 1;
     
	if (*(*(map + x) + y)!='1' )
	{
		p->pos.y = y;
	}

}

void moveRight(player p)//la fonction va vérifier si on peut se déplacer vers la droite et le faire le cas échéant
{
	int x = 0, y = 0;
	x = p->pos.x;
	y = p->pos.y+1;

    if (*(*(map + x) + (y+1))!='1')
	{
		p->pos.y = y;
	}
}

void moveUp(player p)
{
	int  x = 0, y = 0;      
	x = p->pos.x-1;
	y = p->pos.y;

	if (*(*(map + x) + y)!='#')
 	{
		p->pos.x = x;
  	}     
}

void moveDown(player p)
{
	int  x = 0, y = 0;
	x = p->pos.x+1;
	y = p->pos.y;
  
    if (*(*(map + (x+1)) + y) !='#')
    {
		p->pos.x = x;
    }
}
