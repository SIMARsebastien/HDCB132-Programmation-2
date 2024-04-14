#ifndef _DRAWMAP_H_
#define _DRAWMAP_H_

#include "loadMap.h"
#include "player.h"
#include "enemies.h"
#include "midleline.h"
#include "tirs.h"

void drawWall(int *maxX, int *maxY);
void drawML(ML m);
void drawPlayer(player p);
void drawEnemy(enemy e);
void drawPTirs(tirsP p);
void drawAllMLS(listeML m);
void drawAllEnnemis(listeEn e);
void drawAllTirs(listetirsP t);

#endif
