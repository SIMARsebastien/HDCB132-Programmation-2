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
#include "update.h"
#include "save.h"
int blueammo = 30;
int ammo = 30;
int timerSpeedEnnemis=1000;
int timerNewEnnemis=4000;
int mapnumber = 0;
int test = 0;
int level=1;
int mX = 29;
int mY = 41;

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

void Display()
{
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    game(&mX, &mY, p, e, t,li);
	glFlush();
}

int main(int argc, char *argv[])
{
	srand(time(NULL));
	loadMap(&mX, &mY);
	
	e = initialListeEnemies();
    t = initialListeTirs();
	li = loadLine(mX,mY);
	glutInit(&argc, argv);
	glutInitWindowPosition(600,200);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

	glutInitWindowSize((mY-2)*Square_size, mX*Square_size);

	glutCreateWindow("SUPER-BIKKER");

	initRendering();

	glutDisplayFunc(Display);
	glutReshapeFunc(handleResize);
	glutSpecialFunc(SpecialKey);
	
	updates();
	
	glutMainLoop();

	return 0;
}