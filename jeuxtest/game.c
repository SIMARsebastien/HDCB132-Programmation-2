#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "loadMap.h"
#include "drawMap.h"
#include "tirs.h"
#include "enemies.h"
#include "midleline.h"

bool UP = false;
bool LEFT = false;
bool RIGHT = false;
bool DOWN = false;
bool SHOOT = false;
bool CHECKCOLLISION = false;


void Keyboard(unsigned char key, int x, int y)  // fonction allant gérer les input
{
	switch(key)
	{
		case 27:
			exit(0);

		case'z':
			UP = true;
			break;

		case'q':
			LEFT = true;
			break;

		case'd':
			RIGHT = true;
			break;

		case's':
			DOWN = true;
			break;
		
	        case 32:
			SHOOT = true;
			break;		
	}	
}

void game(int *maxX, int *maxY, player p, listeEn e, listetirsP t, listeML m) 
{
	drawWall(maxX, maxY);			//afficher la carte
	drawPlayer(p);
	if (e->starList != NULL || e->endList != NULL)
	{
		drawAllEnnemis(e);
	}	

	if (m->starList != NULL || m->endList != NULL) // pas sur pour ml 
	{
		drawAllMLS(m);
	}	

	if (t->starList != NULL || t->endList != NULL)
	{
		drawAllTirs(t);
	}
	
	glutKeyboardFunc(Keyboard);		//fonction de glut gérant le clavier
	
	if (LEFT == true)
	{
		moveLeft(p);		//va se déplacer vers la gauche si on appuie sur q
		LEFT = false;
	}
	if (RIGHT == true)
	{
		moveRight(p);		//va se déplacer vers la droite si on apppuie sur d
		RIGHT = false;
	}
	if (UP == true)
	{
		moveUp(p);
		UP = false;
	}
	
	if (DOWN == true)
	{
        moveDown(p);
		DOWN = false;
	}
	if (SHOOT == true)
	{
		tirer(p, t);
		SHOOT=false;
	}

	glutPostRedisplay();
}

void checkCollision (enemy e, tirsP p)
{	bool ColX = false;
	bool ColY = false;
	if (p->pos.x + Shoot_size <= e->pos.x && e->pos.x + Square_size <= p->pos.x)
	{
		ColX = true;
	}
	if (p->pos.y + Shoot_size <= e->pos.y && e->pos.y + Square_size <= p->pos.y)
	{
		ColY = true;
	}
	if (ColX && ColY)
	{
		CHECKCOLLISION = true;
	}
	if (CHECKCOLLISION)
	{
		e->active = false;
		p->active = false;
		CHECKCOLLISION = false;
	}
} 