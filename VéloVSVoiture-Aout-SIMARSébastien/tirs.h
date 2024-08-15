#ifndef _TIRS_H_
#define _TIRS_H_

#include <stdbool.h>

#include "player.h"


struct positionT
{
	int x;
	int y;
};
typedef struct tirs tirs;
struct tirs
{
	struct positionT pos;
	bool active;
	int color;
	struct tirs *prevptr;
	struct tirs *nextptr;
};

typedef struct listeTirs listeTirs;
struct listeTirs
{
	
	int quantite;
	struct tirs *starList;
	struct tirs *endList;
	
};

typedef struct tirs *tirsP; 
typedef struct listeTirs *listetirsP;
tirsP createTirs(player p);
listetirsP  initialListeTirs();
void insertionTirs(listetirsP t, tirsP base);
void suppressionTirs(listetirsP t, int test);
void tirer(player p, listetirsP t);
extern tirsP r;
extern listetirsP t;
tirsP createTirs9(int x,int y);
tirsP createTirs8(int x,int y);
listetirsP loadTirs(int mX, int mY);

#endif