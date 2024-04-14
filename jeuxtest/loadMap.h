#ifndef _LOADMAP_H_
#define _LOADMAP_H_

#include <stdbool.h>
//#define MaxX 40
//#define MaxY 41
#define Square_size 20.0
#define Shoot_size 10.0
extern char **map;
extern int mX;
extern int mY;

bool loadMap(int *maxX, int *maxY);

#endif
