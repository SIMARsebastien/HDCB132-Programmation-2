#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "loadMap.h"
#include "drawMap.h"
#include "game.h"
#include "player.h"
#include "enemies.h"
#include "line.h"
#include "tirs.h"
#include "unistd.h"

void updatecheckCollisionplayerandenemis(int valeur)//check la collision entre le joueur et les ennemis 
{
	if ((mapnumber == 2||mapnumber==6) && p->life > 0)
	{
		enemy baseE = e->starList;
		if (e->starList != NULL)
		{
			while(baseE->nextptr!=NULL)
			{
				checkCollisionplayer(baseE);
				baseE = baseE->nextptr;
			}
			checkCollisionplayer(e->endList);
		}
	}
	glutPostRedisplay();
	glutTimerFunc(50, updatecheckCollisionplayerandenemis, 7);
}

void updateCollisionstirsandenemis(int valeur)//check la collision entre ennemis et tirs 
{
	if ((mapnumber == 2||mapnumber==6) && p->life > 0)
	{
		enemy baseE = e->starList;
		tirsP baseT = t->starList;
		if (e->starList != NULL && t->starList != NULL)
		{
			while(baseE->nextptr!=NULL)
			{
				while(baseT->nextptr!=NULL)
				{
					checkCollision(baseE, baseT);
					baseT = baseT->nextptr;
				}
				checkCollision (baseE, t->endList);
				baseE = baseE->nextptr;
				baseT = t->starList;
			}

			while(baseT->nextptr!=NULL)
			{
				checkCollision(e->endList, baseT);
				baseT = baseT->nextptr;
			}
			checkCollision (e->endList, t->endList);
		}
	}
	glutPostRedisplay();
	glutTimerFunc(50, updateCollisionstirsandenemis, 0);
}

void reducescore()//diminue le score si un enemmis passe la barre du bas
{
	if (q->life==3)//plus l'ennemi à de vie plus le jour perd des points. (5points/ennemi-life)
	{
		p->score-=15;
	}
	if (q->life==2)
	{
		p->score-=10;
	}
	if (q->life==1)
	{
		p->score-=5;
	}
}

void ennemimove()//l'ennemi ce déplace vers le joueur
{
	if (p->score>=400 && p->score<=700)
	{
		if (q->pos.x < p->pos.x &&q->pos.x >5 && q->pos.y<p->pos.y)
 		{
			q->pos.y+=1;
 		}
 		if (q->pos.x < p->pos.x&&q->pos.x >5 && q->pos.y>p->pos.y)
 		{
		q->pos.y-=1;
 		}
	}
	
}
void updateEnemies(int valeur)//déplace les ennemis
{
	if ((mapnumber == 2||mapnumber==6) && p->life > 0 && pauseingame!=true)
	{
		q = e->starList;
		if (e->starList != NULL)
		{
			if( q->active!=3)
			{
				q->pos.x += 1;
				ennemimove();
			}	
			if (q->pos.x > 26)
			{ 
				reducescore();
				q->active = 0;
			}
			
			while (q->nextptr != NULL)
			{			
				q = q->nextptr;
				if (q->active!=3)
				{
					q->pos.x +=1;
					ennemimove();

					if (q->pos.x > 26)
					{
						reducescore();
						q->active = 0;
					}
				}
			}
		}
	}
		glutPostRedisplay();
		glutTimerFunc(timerSpeedEnnemis, updateEnemies, 1);		
}

void updateNewEnemies(int valeur)
{
	if ((mapnumber == 2||mapnumber==6) && p->life > 0 && pauseingame!=true)
	{
		enemy new = createEnemy((&mX));
		insertionEnemies(e, new);
	}
	glutPostRedisplay();
	glutTimerFunc(timerNewEnnemis, updateNewEnemies, 3);
}


void updateTirs(int valeur)
{	
	if ((mapnumber == 2||mapnumber==6) && p->life > 0 && pauseingame!=true)
	{
		r = t->starList;
		if (t->starList != NULL)
		{
			r->pos.x -= 1;
			if (r->pos.x <= 1)
			{
				r->pos.x = 30;
				r->active = false;
			}
			while (r->nextptr != NULL)
			{
				r = r->nextptr;
				r->pos.x -= 1;
				if (r->pos.x <= 1)
				{
					r->pos.x = 30;
					r->active = false;
				}
			}
		}
	}
	glutPostRedisplay();
	glutTimerFunc(100, updateTirs, 2);
}


void updateDeleateEnemies(int valeur)
{
	if ((mapnumber == 2||mapnumber==6) && p->life > 0 )
	{
		if (e->starList != NULL || e->endList != NULL)
		{
			suppressionEnemies(e, test);
		}
	}
	glutPostRedisplay();
	glutTimerFunc(30, updateDeleateEnemies, 4);
}

void updateDeleateTirs(int valeur)
{
	if ((mapnumber == 2||mapnumber==6) && p->life > 0)
	{
		if (t->starList != NULL || t->endList != NULL)
		{
			suppressionTirs(t, test);
		}
	}
	glutPostRedisplay();
	glutTimerFunc(50, updateDeleateTirs, 5);
}

void updateLines(int valeur)
{
	if ((mapnumber == 2||mapnumber==6) && p->life > 0 && pauseingame!=true)
	{
		l = li->starList;
		if (li->starList != NULL)
		{
			l->pos.x += 1;
			if (l->pos.x > 27)
			{
				l->pos.x = 0;
			}
			while (l->nextptr != NULL)
			{
				l = l->nextptr;
				l->pos.x +=1;
				if (l->pos.x > 27)
				{
					l->pos.x = 0;
				}
			}
		}
	}
	glutPostRedisplay();
	glutTimerFunc(500, updateLines, 6);
}

void updates()
{
    glutTimerFunc(50, updateCollisionstirsandenemis, 0);
	glutTimerFunc(50, updatecheckCollisionplayerandenemis,7);
	glutTimerFunc(50, updateEnemies, 1);
	glutTimerFunc(50, updateTirs, 2);
	glutTimerFunc(1000, updateNewEnemies, 3); //apparition du premier ennemi //délai de la première apparition 
	glutTimerFunc(20, updateDeleateEnemies, 4);
	glutTimerFunc(50, updateDeleateTirs, 5);
	glutTimerFunc(40, updateLines, 6);
}