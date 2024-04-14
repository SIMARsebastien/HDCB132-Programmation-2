#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "moto2.c"
#include <stdio.h>
#include <stdlib.h>
#include "loadMap.h"
#include "drawMap.h"
#include "game.h"

void drawSky()
{
        glBegin(GL_POLYGON); 
            glColor3f(0,0,0);
	
            glVertex3f(Square_size, 30*Square_size, 1);
            glVertex3f(Square_size, Square_size, 1);
            glVertex3f(30*Square_size, 0, 1);
            glVertex3f(30*Square_size, 30*Square_size, 1);
        glEnd();
}

void drawWall(int *maxX, int *maxY)			// fonction qui affiche les murs et les plateformes
{	
	for (int j = 0; j < (*maxX); ++j)
	{
		for (int i = 0; i < (*maxY); ++i)
		{
			drawSky();
			if(*(*(map + j) + i) == '#')
			{
                glColor3f(1.0f,1.0f,1.0f);
				glMatrixMode(GL_MODELVIEW);
				
			    glLoadIdentity();
				glTranslatef(i*Square_size,j*Square_size,0.0f);
				glBegin(GL_QUADS);
				glColor3f(0.4,0.2,0);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(Square_size, 0.0f, 0.0f);
				glVertex3f(Square_size,Square_size, 0.0f);
				glVertex3f(0.0f,Square_size, 0.0f);

				glEnd();
			}

				if(*(*(map + j) + i) == '1' || *(*(map + j) + i) =='3')
			{
                glColor3f(1.0f,1.0f,1.0f);
				glMatrixMode(GL_MODELVIEW);
				
			    glLoadIdentity();
				glTranslatef(i*Square_size,j*Square_size,0.0f);
				glBegin(GL_QUADS);
				glColor3f(1.0,1,1);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(Square_size, 0.0f, 0.0f);
				glVertex3f(Square_size,Square_size, 0.0f);
				glVertex3f(0.0f,Square_size, 0.0f);

				glEnd();	
			}
				if(*(*(map + j) + i) == '2')
			{
                glColor3f(1.0f,1.0f,1.0f);
				glMatrixMode(GL_MODELVIEW);
				
			    glLoadIdentity();
				glTranslatef(i*Square_size,j*Square_size,0.0f);
				glBegin(GL_QUADS);
				glColor3f(0,1,0);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(Square_size, 0.0f, 0.0f);
				glVertex3f(Square_size,Square_size, 0.0f);
				glVertex3f(0.0f,Square_size, 0.0f);

				glEnd();	
			}
		}
	}
}

void drawPlayer(player p)
{
	int i, j;
	i = p->pos.x;
	j = p->pos.y;
	
	glColor3f(0.0f,1.0f,0.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	

	glTranslatef(j*Square_size,i*Square_size,0.0f);

	glBegin(GL_QUADS);

	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(2*Square_size, 0.0f, 0.0f);
	glVertex3f(2*Square_size,2*Square_size, 0.0f);
	glVertex3f(0.0f,2*Square_size, 0.0f);

	glEnd();
}

void drawEnemy(enemy e)	
{
	int i, j;
	i = e->pos.x;
	j = e->pos.y;
	glColor3f(1.0f,0.0F,0.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	int texture;
	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	gluBuild2DMipmaps(GL_TEXTURE_2D,moto2.bytes_per_pixel, moto2.width, moto2.height,GL_RGB,GL_UNSIGNED_BYTE,moto2.pixel_data);
	glEnable(GL_TEXTURE_2D);
	/*int texture;
	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	gluBuild2DMipmaps(GL_TEXTURE_2D,SUPERMAN.bytes_per_pixel, SUPERMAN.width, SUPERMAN.height,GL_RGB,GL_UNSIGNED_BYTE,SUPERMAN.pixel_data);
	glEnable(GL_TEXTURE_2D);*/
	
	glTranslatef(j*Square_size,i*Square_size,0.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0,1.0); glVertex3f(0.0f,0.0f,0.0f);
	glTexCoord2f(1.0,1.0); glVertex3f(2*Square_size,0.0f,0.0f);
	glTexCoord2f(1.0,0.0); glVertex3f(2*Square_size,2*Square_size,0.0f);
	glTexCoord2f(0.0,0.0); glVertex3f(0.0f,2*Square_size,0.0f);
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
}

void drawTirs(tirsP p)
{
	int i, j;
	i = p->pos.x;
	j = p->pos.y;
	glColor3f(0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(j*Shoot_size,i*Shoot_size,0.0f);
	glBegin(GL_QUADS);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(Shoot_size,0.0f,0.0f);
	glVertex3f(Shoot_size,Shoot_size,0.0f);
	glVertex3f(0.0f,Shoot_size,0.0f);
	glEnd();
}

void drawAllEnnemis(listeEn e)
{	
	enemy first = malloc(sizeof(enemies));
	enemy next = malloc(sizeof(enemies));
	first = e->starList;
	next = e->starList->nextptr;
	if (e->starList != NULL || e->endList != NULL)
	{
		drawEnemy(first);
		if (e->starList->nextptr != NULL)
		{
			drawEnemy(next);
			while (next->nextptr != NULL)
			{
				next = next->nextptr;
				drawEnemy(next);
			}
		}
	}
}

void drawAllTirs(listetirsP t)
{
	tirsP first = malloc(sizeof(tirs));
	tirsP next = malloc(sizeof(tirs));
	first = t->starList;
	if (t->starList != NULL && t->starList->nextptr != NULL)
	{
	next = t->starList->nextptr;
	}
	if (t->starList != NULL || t->endList != NULL)
	{
		drawTirs(first);
		if (t->starList->nextptr != NULL)
		{
			drawTirs(next);
			while (next->nextptr != NULL)
			{
				next = next->nextptr;
				drawTirs(next);
			}
		}
	}
}

void drawML(ML m)	//midleline
{
	int i, j;
	i = m->pos.x;
	j = m->pos.y;
	glColor3f(0.0f,0.0F,0.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	/*int texture;
	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	gluBuild2DMipmaps(GL_TEXTURE_2D,SUPERMAN.bytes_per_pixel, SUPERMAN.width, SUPERMAN.height,GL_RGB,GL_UNSIGNED_BYTE,SUPERMAN.pixel_data);
	glEnable(GL_TEXTURE_2D);*/
	
	glTranslatef(j*Square_size,i*Square_size,0.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0,1.0); glVertex3f(0.0f,0.0f,0.0f);
	glTexCoord2f(1.0,1.0); glVertex3f(Square_size,0.0f,0.0f);
	glTexCoord2f(1.0,0.0); glVertex3f(Square_size,Square_size,0.0f);
	glTexCoord2f(0.0,0.0); glVertex3f(0.0f,Square_size,0.0f);
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
}

void drawAllMLS(listeML m)
{	
	ML first = malloc(sizeof(MLS));
	ML next = malloc(sizeof(MLS));
	first = m->starList;
	next = m->starList->nextptr;
	if (m->starList != NULL || m->endList != NULL)
	{
		drawML(first);
		if (m->starList->nextptr != NULL)
		{
			drawML(next);
			while (next->nextptr != NULL)
			{
				next = next->nextptr;
				drawML(next);
			}
		}
	}
}