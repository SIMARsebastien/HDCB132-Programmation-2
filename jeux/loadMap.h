#ifndef _LOADMAP_H_
#define _LOADMAP_H_
#include "line.h"
#include <stdbool.h>

#define Square_size 20.0
#define Shoot_size 10.0
extern char **map;
extern int mX;
extern int mY;
extern int mapnumber;
bool loadMap(int *maxX, int *maxY);

#endif
