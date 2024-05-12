#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "loadMap.h"
#include "tirs.h"
#include"enemies.h"
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

	    fclose(f);
		
	    printf("\n");

		for(i = 0; i < (*maxX); i++)
		{
			for(j = 0; j < (*maxY); j++)
			{
				printf("%c", *(*(map + i) + j));
			}
			printf("\n");
		}
	
 return true;
 }		

