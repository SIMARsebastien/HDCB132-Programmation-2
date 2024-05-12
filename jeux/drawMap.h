#ifndef _DRAWMAP_H_
#define _DRAWMAP_H_

#include "loadMap.h"
#include "player.h"
#include "enemies.h"
#include "tirs.h"
#include"line.h"

void drawWall(int *maxX, int *maxY);
void drawEdges();
void drawLevel();
void drawPlayer(player p);
void drawEnemy(enemy e);
void drawPTirs(tirsP p);
void drawLines(line l);
void drawAllEnnemis(listeEn e);
void drawAllTirs(listetirsP t);
void drawAllLines(listeLi li);
void vBitmapOutput(int x, int y, char *string, void *font);
void vStrokeOutput(GLfloat x, GLfloat y, char *string, void *font);
void textmenu();
void drawtextacceuil();
void drawPause();
void drawChoiceinGame();
void drawCredits();
void drawOptions();
void drawhp();
void drawScores();

void drawGameOver();
void drawScore();
void drawLife();
void drawBlueAmmo();
void drawAmmo();
#endif
