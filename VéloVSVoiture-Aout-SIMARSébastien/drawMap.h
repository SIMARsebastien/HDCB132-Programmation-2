#ifndef _DRAWMAP_H_
#define _DRAWMAP_H_

#include <GL/glut.h>

#include "loadMap.h"
#include "player.h"
#include "enemies.h"
#include "tirs.h"
#include"line.h"

void drawSky();
void drawEdges();
void drawWall(int *maxX, int *maxY);
void drawPlayer(player p);
void drawEnemy(enemy e);
void drawPTirs(tirsP p);
void drawAllEnnemis(listeEn e);
void drawAllTirs(listetirsP t);
void drawLines(line l);
void drawAllLines(listeLi li);
void vStrokeOutput(GLfloat x, GLfloat y, char *string, void *font);
void vBitmapOutput(int x, int y, char *string, void *font);
void textmenu();
void drawScore();
void drawLife();
void drawBlueAmmo();
void drawAmmo();
void drawName();
void drawGameOver();
void drawPause();
void drawChoiceinGame();
void drawtextacceuil();
void drawChooseName();
void drawCredits();
void drawOptions();
void drawhp();
void drawLevel();
void drawScores();

#endif
