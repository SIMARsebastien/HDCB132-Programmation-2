#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <string.h>

#include "scores.h"
#include "player.h"
#include "game.h"
int tabScores[5];
char tabNamesScores[5] [15];

void compareScores()//compare le score en fin de game avec le tableau des meilleurs score (change les scores en cas échéant aisi que les noms associés).
{
    int i=0;
    int j = 4;
    while (p->score <= tabScores[i])
    {
        i++;
    }
    while (j>i)
    {
       tabScores[j]=tabScores[j-1];
        strcpy(tabNamesScores[j],tabNamesScores[j-1]);
       j--;
    }
    tabScores[i]=p->score;
    strcpy(tabNamesScores[i],playernamearray);    
}