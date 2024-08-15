#ifndef _GAME_H_
#define _GAME_H_

#include <stdio.h>
#include <stdlib.h>

#include "save.h"
#include "loadMap.h"
#include "drawMap.h"
#include "tirs.h"
#include "enemies.h"
#include "scores.h"

extern int blueammo;
extern int ammo;
extern int test;
extern int level;
extern bool pauseingame;
extern int timerEnnemis;
extern int timerNewEnnemis;
extern int timerSpeedEnnemis;
extern int idleMouseX;
extern int idleMouseY;
extern char playernamearray[15];
extern int playerNameSize;

void idleMouse (int x, int y );
void clearennemis();
void cleartirs();
void clearline();
void mouse (int button, int state, int x, int y ); 
void Keyboard(unsigned char key, int x, int y);
void SpecialKey(int key, int x, int y);
void moveplayer();
void checkCollisionplayerchoix();
void game(int *maxX, int *maxY, player p, listeEn e, listetirsP  t,listeLi li);
void checkCollision (enemy e, tirsP r);
void checkCollisionplayer(enemy e);

#endif
