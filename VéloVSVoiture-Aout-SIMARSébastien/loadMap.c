#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "loadMap.h"
#include "tirs.h"
#include"enemies.h"
#include "game.h"
#include "scores.h"
char **map;

bool loadMap(int *maxX, int *maxY)		//fonction qui ouvre le fichier txt et charge la carte dans le tableau
{
    map = malloc(sizeof(char *) * (*maxX));	
    FILE *f = NULL;
	if (mapnumber==0)
	{
		f = fopen("mapstart.txt", "r");
	}
	if(mapnumber == 1)
	{
   		f = fopen("mapmenu.txt", "r");
	}
	if(mapnumber == 2)
	{
    	f = fopen("map1.txt", "r");
	}
	if (mapnumber ==3)
	{
		f = fopen("mapCREDITS.txt", "r");
	}
	if (mapnumber ==4)
	{
		f = fopen("mapOptions.txt", "r");
	}
	if (mapnumber ==5)
	{
		f = fopen("mapSCORES.txt", "r");
	}
	if (mapnumber==6)
	{
		f = fopen("save1.txt", "r");
	}
	
    if (f == NULL)
    {
        printf("file empty");
        return false;
    }
    char c;
    int i=0;
    int j= 0;
    for(i = 0; i < (*maxX); i++)
		{
		*(map + i) = malloc(sizeof(char *) * (*maxY));	
			for(j = 0; j < (*maxY); j++)
			{		
				c = fgetc(f);
				*(*(map + i) + j) = c;
			}
			fgetc(f);
		}
	if ((mapnumber==6 ||mapnumber==2)  && i == (*maxX))//charge les info du player de la save
	{
		fscanf(f,"%d %d %d %d %d",&level,&p->life,&p->score,&ammo,&blueammo);
		printf("%d %d %d %d %d",level,p->life,p->score,ammo,blueammo);

		int x = 0, y = 0;
		for (int k = 0; k < *maxX; ++k)
		{
			for (int j = 0; j < *maxY; ++j)
			{
				if(*(*(map +k) + j) == 'X')
				{
					x = k;
					y = j;
				}
			}
		}	
		p->pos.x = x;
		p->pos.y = y;
		i++;
	}
	if (mapnumber==6 && i == (*maxX)+1)//charge le nom du player de la save
	{
		fscanf(f,"%s",playernamearray);
	}
	    fclose(f);
		
	   /* printf("\n"); // imprime la carte de jeu dans la fenetre de commande

		for(i = 0; i < (*maxX); i++)
		{
			for(j = 0; j < (*maxY); j++)
			{
				printf("%c", *(*(map + i) + j));
			}
			printf("\n");
		}
	*/
 return true;
 }	

void loadScores()//charge les scores à partir du fichier texte
{
	char nom[25];
	int i=0;
    FILE *f = NULL;
	
	f = fopen("saveScores.txt", "r");
	
    fscanf(f,"%d %d %d %d %d",&tabScores[0], &tabScores[1], &tabScores[2], &tabScores[3], &tabScores[4]);
	
	for ( i=0; i < 5; i++)
	{		
		fscanf(f,"%s",nom);
		strcpy(tabNamesScores[i],nom);			
	}	
	fclose(f);
}	
