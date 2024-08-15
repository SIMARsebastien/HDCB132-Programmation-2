#ifndef _LINE_H_
#define _LINE_H_
#include <stdbool.h>

typedef struct positionL positionL;
struct positionL
{
	int x;
	int y;
};
typedef struct lines lines;
struct lines
{
	struct positionL pos;
	struct lines *prevptr;
	struct lines *nextptr;
};

typedef struct listeLines listeLines;
struct listeLines
{
	
	int quantite;
	struct lines *starList;
	struct lines *endList;
	
};

typedef struct lines *line; 
typedef struct listeLines *listeLi;
line createLine(int x,int y);
listeLi  initialListeLine();
listeLi loadLine(int mx, int mY);
void insertionLines(listeLi li, line l);
extern line l;
extern listeLi li;

#endif