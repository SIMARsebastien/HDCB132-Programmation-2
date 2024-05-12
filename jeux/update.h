#ifndef _UPDATE_H_
#define _UPDATE_H_

#include <stdlib.h>
#include <stdio.h>
#include "game.h"

void updatecheckCollisionplayerandenemis(int valeur);
void updateCollisionstirsandenemis(int valeur);
void reducescore();
void ennemimove();
void updateEnemies(int valeur);
void updateNewEnemies(int valeur);
void updateTirs(int valeur);
void updateDeleateEnemies(int valeur);
void updateDeleateTirs(int valeur);
void updateLines(int valeur);
void updates();

#endif