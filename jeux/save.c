#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "loadMap.h"
#include "player.h"
#include "line.h"
#include "enemies.h"
#include "tirs.h"
#include"save.h"
//#include "game.h"
//#include "loadMap.h"

void saveMap()
{    
    FILE *f = NULL;
	if ((mapnumber == 2||mapnumber==6))
	{
		f = fopen("save1.txt", "w");
	}

    int i=0;
    int j= 0;
    int test;
	for(i = 0; i < (mX); i++)
	{	
		for(j = 0; j <= (mY); j++)
		{	
            test=0;
            if (j==41&& test ==0)
            {
                fputc('\n',f);
                test=1;
            }
            if (j==40 && test==0)
            {
                fputc('/',f);
                test=1;
            }
            if ((i==0 || i==28) && j!=40&& test ==0)
            {
                fputc('#',f);
                test=1;
            }
            if ((j==0 || j==39)&& test ==0)
            {
                fputc('0',f);
                test=1;
            }
            if ((j==7||j==31)&& test ==0)
            {
                fputc('1',f);
                test=1;
            }
            if (j==19&& test ==0)
            {
                fputc('4',f);
                test=1;
            }
            if (((j>=1 && j<7) || (j>=32 && j<=38))&&test==0 )
            {
                fputc('2',f);
                test=1;
            }
            l = li->starList;
            if (li->starList != NULL)
	        {
		        if(i== l->pos.x && j ==l->pos.y && test==0)
                {
                    fputc('3',f);
                    test=1;
                }	
                while (l->nextptr != NULL)
                {			
                    l = l->nextptr;
                    if (i== l->pos.x && j ==l->pos.y && test==0)
                    {
                        fputc('3',f);
                        test=1;
                    }
                }
	        }
            q = e->starList; //save la liste d'ennemis
		    if (e->starList != NULL)
	        {
		        if( q->active!=3 && i==q->pos.x && j ==q->pos.y &&test==0)
                {
                    if (q->life==1)
                    {
                        fputc('7',f);
                        test=1;
                    }
                    else if (q->life==2)
                    {
                        fputc('g',f);
                        test=1;
                    }
                       else if (q->life==3)
                    {
                        fputc('h',f);
                        test=1;
                    }   
                }	
                if (q->active==3 && i==q->pos.x && j ==q->pos.y &&test ==0)
                {
                     if (q->life==1)
                    {
                        fputc('i',f);
                        test=1;
                    }
                    else if (q->life==2)
                    {
                        fputc('j',f);
                        test=1;
                    }
                       else if (q->life==3)
                    {
                        fputc('k',f);
                        test=1;
                    }   
                }
                while (q->nextptr != NULL)
                {			
                    q = q->nextptr;
                    if (q->active!=3 && i==q->pos.x && j ==q->pos.y&& test==0)
                    {
                        fputc('7',f);
                        test=1;
                    }
                    if (q->active==3 && i==q->pos.x && j ==q->pos.y&& test==0)
                    {
                        fputc('f',f);
                        test=1;
                    }
                }
		    }
            r = t->starList;
            if (t->starList != NULL)
	        {
		        if( r->color==1 && i==r->pos.x && j ==r->pos.y&& test ==0)
                {
                    fputc('8',f);
                    test=1;
                }	
                if (r->color==2 && i==r->pos.x && j ==r->pos.y&& test ==0)
                {
                    fputc('9',f);
                    test=1;
                }
                while (r->nextptr != NULL)
                {			
                    r = r->nextptr;
                    if (r->color==1  && i==r->pos.x && j ==r->pos.y&& test ==0)
                    {
                        fputc('8',f);
                        test=1;
                    }
                    if (r->color==2 && i==r->pos.x && j ==r->pos.y&& test ==0)
                    {
                        fputc('9',f);
                        test=1;
                    }
                }
		    }
            if (i==p->pos.x && j==p->pos.y)
            {
                if (test==0)
                {
                    fputc('X',f);
                    test=1;
                }
                else if (test==1)
                {
                    p->pos.y++;
                }    
            }
            if (test==0)
            {
                fputc('.',f);
            }
        }		
    }
}
             
			
	
		

