#ifndef _MIDLELINE_H_
#define _MIDLELINE_H_

#include <stdbool.h>

struct positionML
{
	int x;
	int y;
};
typedef struct MLS MLS;
struct MLS
{
	int vie;
	struct positionML pos;
	bool active;
	struct MLS *prevptr;
	struct MLS *nextptr;
};

typedef struct listeMLS listeMLS;
struct listeMLS
{
	
	int quantite;
	struct MLS *starList;
	struct MLS *endList;
	
};

typedef struct MLS *ML; 
typedef struct listeMLS *listeML;
ML createML(int *maxY);
listeML  initialListeMLS();
void insertionMLS(listeML m, ML k);
void suppressionMLS(listeML m, bool test);
extern ML k;
extern listeML m;

#endif
