#ifndef _GAME_H_
#define _GAME_H_

#include <stdio.h>
#include <stdlib.h>
extern int blueammo;
extern int ammo;
extern int test;
extern int level;
extern bool pauseingame;
extern int timerEnnemis;
extern int timerNewEnnemis;
extern int timerSpeedEnnemis;
void Keyboard(unsigned char key, int x, int y);
void SpecialKey(int key, int x, int y);
void game(int *maxX, int *maxY, player p, listeEn e, listetirsP  t,listeLi li);
void checkCollision (enemy e, tirsP r);
void checkCollisionplayer(enemy e);
void checkCollisionplayerchoix();
void clearennemis();
void cleartirs();
void clearline();
void CheckNegativScore();

#endif
