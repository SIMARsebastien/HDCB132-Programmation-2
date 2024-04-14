#ifndef _GAME_H_
#define _GAME_H_

#include <stdio.h>
#include <stdlib.h>

void Keyboard(unsigned char key, int x, int y);
void game(int *maxX, int *maxY, player p, listeEn e, listetirsP  t, listeML m); // pas sur pour ml
void checkCollision (enemy e, tirsP p);


#endif
