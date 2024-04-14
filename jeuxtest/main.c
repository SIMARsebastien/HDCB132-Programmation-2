#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "midleline.h"
#include "midleline.c"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "loadMap.h"
#include "drawMap.h"
#include "game.h"
#include "player.h"
#include "enemies.h"

#include "tirs.h"

bool test = false;


void updateCollisions(int valeur)
{
	enemy baseE = e->starList;
	tirsP baseP = t->starList;
	if (e->starList != NULL && t->starList != NULL)
	{
		checkCollision(baseE, baseP);
		if (t->starList->nextptr != NULL)
			{
				baseP = baseP->nextptr;	
				checkCollision(baseE, baseP);
				while (baseP->nextptr != NULL)
				{
					baseP = baseP->nextptr;
					checkCollision(baseE, baseP);
				}
			}
		if (e->starList->nextptr != NULL)
		{
			baseE = baseE->nextptr;
			baseP = t->starList;
			checkCollision(baseE, baseP);
			if (t->starList->nextptr != NULL)
			{
				baseP = baseP->nextptr;
				checkCollision (baseE, baseP);
				while (baseP->nextptr != NULL)
				{
					baseP = baseP->nextptr;
					checkCollision(baseE, baseP);
				}
			}
			while (baseE->nextptr != NULL)
			{
				baseE = baseE->nextptr;
				baseP = t->starList;
				checkCollision(baseE, baseP);
				if (t->starList->nextptr != NULL)
				{
					baseP = baseP->nextptr;
					checkCollision (baseE, baseP);
					while (baseP->nextptr != NULL)
					{
						baseP = baseP->nextptr;
						checkCollision(baseE, baseP);
					}
				}
			}
		}
	}
	glutPostRedisplay();
	glutTimerFunc(50, updateCollisions, 0);
}

void updateEnemies(int valeur)
{
	q = e->starList;
	if (e->starList != NULL)
	{
		q->pos.x += 1;
		if (q->pos.x > 27)
		{
			q->pos.x = 2;
			q->active = false;
		}
		while (q->nextptr != NULL)
		{
			q = q->nextptr;
			q->pos.x +=1;
			if (q->pos.x > 27)
			{
				q->pos.x = 2;
				q->active = false;
			}
		}
	}
	glutPostRedisplay();
	glutTimerFunc(500, updateEnemies, 1);
}

void updateNewEnemies(int valeur)
{
	enemy new = createEnemy((&mX));
	insertionEnemies(e, new);
	glutPostRedisplay();
	glutTimerFunc(4000, updateNewEnemies, 3);
}

void updateTirs(int valeur)
{
	r = t->starList;
	if (t->starList != NULL)
	{
		r->pos.x -= 1;
		if (r->pos.x <= 1)
		{
			r->pos.x = 88;
			r->active = false;
		}
		while (r->nextptr != NULL)
		{
			r = r->nextptr;
			r->pos.x -= 1;
			if (r->pos.x <= 1)
			{
				r->pos.x = 88;
				r->active = false;
			}
		}
	}
	glutPostRedisplay();
	glutTimerFunc(50, updateTirs, 2);
}

void updateDeleateEnemies(int valeur)
{
	if (e->starList != NULL || e->endList != NULL)
	{
		suppressionEnemies(e, test);
	}
	glutPostRedisplay();
	glutTimerFunc(200, updateDeleateEnemies, 4);
}

void updateDeleateTirs(int valeur)
{
	if (t->starList != NULL || t->endList != NULL)
	{
		suppressionTirs(t, test);
	}
	glutPostRedisplay();
	glutTimerFunc(50, updateDeleateTirs, 5);
}

void updateMLS(int valeur)
{
	k = m->starList;
	if (m->starList != NULL)
	{
		k->pos.x += 1;
		if (k->pos.x > 28)
		{
			k->pos.x = 2;
			k->active = false;
		}
		while (k->nextptr != NULL)
		{
			k = k->nextptr;
			k->pos.x +=1;
			if (k->pos.x > 28)
			{
				k->pos.x = 2;
				k->active = false;
			}
		}
	}
	glutPostRedisplay();
	glutTimerFunc(500, updateMLS, 6);
}

void updateNewMLS(int valeur)
{
	ML new = createML((&mX));
	insertionMLS(m, new);
	glutPostRedisplay();
	glutTimerFunc(1000, updateNewMLS, 7);//temps d'apparition entre deux trait
}

void updateDeleateMLS(int valeur)
{
	if (m->starList != NULL || m->endList != NULL)
	{
		suppressionMLS(m, test);
	}
	glutPostRedisplay();
	glutTimerFunc(200, updateDeleateMLS, 8);
}

void initRendering()
{
	glEnable(GL_DEPTH_TEST);
}

void handleResize(int width,int heigth)
{
	glViewport(0, 0, width, heigth);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, heigth, 0);
}

void affichage()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glRasterPos2f(30,30);
	const char *text = "Vie:";
	int length =strlen(text);
	for (int i=0;text[i] !=length;i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}
		glFlush();
}

void Display()
{
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    game(&mX, &mY, p, e, t, m);
	glFlush();
}

int main(int argc, char *argv[])
{
	mX = 30;
	mY = 41;
	srand(time(NULL));
	loadMap(&mX, &mY);
	p = createPlayer(&mX, &mY);
	e = initialListeEnemies();
    t = initialListeTirs();
	m = initialListeMLS();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

	glutInitWindowSize((mY-2)*Square_size, mX*Square_size);

	glutCreateWindow("SUPER-BIKKER");

	initRendering();
    glutDisplayFunc(affichage);
	glutDisplayFunc(Display);
	glutReshapeFunc(handleResize);
	glutTimerFunc(50, updateCollisions, 0);
	glutTimerFunc(40, updateEnemies, 1);
	glutTimerFunc(50, updateTirs, 2);
	glutTimerFunc(2000, updateNewEnemies, 3); //apparition du premier ennemi
	glutTimerFunc(20, updateDeleateEnemies, 4);
	glutTimerFunc(50, updateDeleateTirs, 5);
	glutTimerFunc(50, updateMLS, 6);
	glutTimerFunc(10, updateNewMLS, 7); //apparition du premier ennemi
	glutTimerFunc(20, updateDeleateMLS, 8);
	
	glEnable(GL_DEPTH_TEST);
	
	glutMainLoop();

	return 0;
}