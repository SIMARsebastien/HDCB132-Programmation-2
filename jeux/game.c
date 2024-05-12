#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "save.h"
#include "loadMap.h"
#include "drawMap.h"
#include "tirs.h"
#include "enemies.h"
bool pauseingame = false;
bool UP = false;
bool LEFT = false;
bool RIGHT = false;
bool DOWN = false;
bool SHOOT = false;
bool CHECKCOLLISION = false;
bool maptest6=false;
void clearennemis()//vide la liste de ennemis
{
	if (e->starList != NULL || e->endList != NULL)
	{
		enemy base = e->starList;
		if (base!=NULL)
		{
			while (base->nextptr!=NULL)
			{
				base=base->nextptr;
				base->prevptr=NULL;

				free(e->starList);
				e->starList=base;
			}
			e->starList=NULL;
			e->endList=NULL;
			e->quantite=0;
		}
	}
}

void cleartirs() //vide la liste des tirs
{
	if (t->starList != NULL || t->endList != NULL)
	{
		tirsP base = t->starList;
		if (base!=NULL)
		{
			while (base->nextptr!=NULL)
			{
				base=base->nextptr;
				base->prevptr=NULL;

				free(t->starList);
				t->starList=base;
			}
			t->starList=NULL;
			t->endList=NULL;
			t->quantite=0;
		}
	}
}

void clearline() //vide la liste des lignes
{
	if (li->starList != NULL || li->endList != NULL)
	{
		line base = li->starList;
		if (base!=NULL)
		{
			while (base->nextptr!=NULL)
			{
				base=base->nextptr;
				base->prevptr=NULL;

				free(li->starList);
				li->starList=base;
			}
			li->starList=NULL;
			li->endList=NULL;
			li->quantite=0;
		}
	}
}

void Keyboard(unsigned char key, int x, int y)  // fonction allant gérer les input
{
	switch(key)
	{
		case 'e': //changement d'armes
			if (p->weapon==false)
			{
				p->weapon =true;
			}
			else if (p->weapon==true)
			{
				p->weapon =false;
			}
		break; 

		case'l'://load game
			if (((mapnumber == 2||mapnumber==6) && pauseingame==true) )
			{
				clearennemis();//void listes 
				cleartirs();
				clearline();
				mapnumber=6;
				maptest6=true;
				loadMap(&mX, &mY);
				loadLine(mX,mY);
				loadEnnemis(mX,mY);
				loadTirs(mX,mY);
				
			}
			if (mapnumber ==1 &&pauseingame==true)
			{
				clearennemis();//void listes 
				cleartirs();
				clearline();
				mapnumber=6;
				maptest6=true;
				loadMap(&mX, &mY);
				loadLine(mX,mY);
				loadEnnemis(mX,mY);
				loadTirs(mX,mY);
				
			}
			break;
			
		case 27: //(esc)
		if (mapnumber==0) //exit
		{
			exit(0);
			break;
		}
		else if (mapnumber==1)
		{
			mapnumber=0;
			loadMap(&mX, &mY);
		}
		
		else if ((mapnumber == 2||mapnumber==6) && p->life>0) //pause
		{
			if (pauseingame == true)
			{
				pauseingame = false;
			}
			else
			{
				pauseingame = true;
			}
		}
		else if (mapnumber==3 || mapnumber==4)//resume
		{
			mapnumber=1;
			loadMap(&mX, &mY);
		}
		break;

		case'o': //options
			if (mapnumber==1)
			{
				mapnumber=4;
				loadMap(&mX, &mY);
			}
			else if(mapnumber==4 && pauseingame==false)
			{
				mapnumber = 1;
				loadMap(&mX, &mY);
			}
			else if ((mapnumber == 2||mapnumber==6) && pauseingame==true)
			{
				mapnumber=4;
				loadMap(&mX, &mY);
			}
			else if (mapnumber==4 && pauseingame==true &&maptest6==false)
			{
				mapnumber=2;
				loadMap(&mX, &mY);
			}
			else if (mapnumber==4 && pauseingame==true &&maptest6==true)
			{
				mapnumber=6;
				loadMap(&mX, &mY);
			}				
		break;

		case 'n'://new game
			if (mapnumber ==1 || (mapnumber ==2 && pauseingame==true))
			{
				//maptest6=true;
				clearennemis();//void listes 
				cleartirs();
				clearline();
				pauseingame=false;
				mapnumber =2;
				loadMap(&mX, &mY);
				loadLine(mX,mY);
				loadEnnemis(mX,mY);
				loadTirs(mX,mY);			
				p = createPlayer(&mX, &mY);
				blueammo = 30;
				ammo= 30;
			}
		break;
		case'm': //main menu 
			if (pauseingame==true)
			{
				
				mapnumber =1;
				loadMap(&mX, &mY);
				pauseingame=false;
			}
		break;
		case 'c': //crédits
			if(mapnumber==1)
			{
				mapnumber =3;
				loadMap(&mX, &mY);
			}
			 else if(mapnumber==3)
			{
				mapnumber =1;
				loadMap(&mX, &mY);
			}
		break;
					
		case'z'://allez vers le haut
			UP = true;
			break;
		case'q'://allez a gauche
			LEFT = true;
			break;
		case'd'://droite
			RIGHT = true;
			break;
		case's'://bas
			if (mapnumber==1) //acceuil
			{
				mapnumber =5;//map score
				loadMap(&mX, &mY);
			}
			else if (mapnumber==5)
			{
				mapnumber=1;
				loadMap(&mX, &mY);
			}
			else if ((mapnumber==2||mapnumber==6)&&pauseingame==true)//map jeu //map loadgame
			{
				saveMap();
			}
			else 
			{
				DOWN = true;
			}
			break;

	    case 32: //bar espace
			if (mapnumber==0)
			{
				mapnumber=1;
				loadMap(&mX, &mY);
			}
			if ((mapnumber == 2||mapnumber==6))
			{
				if (ammo>0 && p->weapon == false && pauseingame!=true)
				{
					SHOOT = true;
					ammo-=1;
				}
				if (blueammo>0 && p->weapon ==true &&pauseingame!=true)
				{
					SHOOT = true;
					blueammo-=1;
				}
			}
		break;		
	}	
}

void SpecialKey(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP :
			UP = true;
			break;
		case GLUT_KEY_LEFT :
			LEFT = true;
			break;
		case GLUT_KEY_RIGHT :
			RIGHT = true;
			break;
		case GLUT_KEY_DOWN :
			DOWN = true;	
			break;
	}
}

void moveplayer()
{
	if (pauseingame!=true)
	{
			if (LEFT == true)
			{
				moveLeft(p);		//va se déplacer vers la gauche si on appuie sur q
				LEFT = false;
			}
			if (RIGHT == true)
			{
				moveRight(p);		//va se déplacer vers la droite si on apppuie sur d
				RIGHT = false;
			}
			if (UP == true)
			{
				moveUp(p);
				UP = false;
			}
			
			if (DOWN == true)
			{
				moveDown(p);
				DOWN = false;
			}
			if (SHOOT == true)
			{
				tirer(p, t);
				SHOOT=false;
			}
	}	
}

 void checkCollisionplayerchoix() //ds le menu game over permet de choisir une action en entrant en collision avec le carré désiré
 	{	
		if (p->pos.x < 3 && p->pos.y < 5) // haut gauche (mainmenu)
		{
			mapnumber =1; //retourner au main menu
			//clearennemis();//void listes 
			//cleartirs();
			//clearline();
			loadMap(&mX, &mY);
			blueammo = 30;
			ammo= 30;
		}
		if (p->pos.x > 23 && p->pos.y < 5) // bas gauche (restart)
		{
			clearennemis();//void listes
			cleartirs();
			clearline();
		
			maptest6=false;
			mapnumber =2;
			loadMap(&mX, &mY);
			loadEnnemis(mX,mY);
				loadTirs(mX,mY);
				loadMap(&mX, &mY);
				
				loadLine(mX,mY);
			blueammo = 30;
			ammo= 30;
			p = createPlayer(&mX, &mY);
			
		}
		if (p->pos.x < 3 && p->pos.y > 32) //haut droite (loadgame)
		{		
				p->pos.x=25;
				p->pos.y=15;
				clearennemis();//void listes 
				cleartirs();
				clearline();
				p->life = 3;
				
				mapnumber=6;
				maptest6=true;
				loadMap(&mX, &mY);
				loadEnnemis(mX,mY);
				loadTirs(mX,mY);
				
				
				loadLine(mX,mY);
				
		}
    }

void game(int *maxX, int *maxY, player p, listeEn e, listetirsP t, listeLi li)//  fonction qui gère tout les draw et toute les fonctions clavier 
{
	
	if (mapnumber ==0)//faire une image du jeux immitant un chargement ... quelques seconde avant de passer irectement a mapnumber2//to do 
	{
		drawtextacceuil();
	}
	if (mapnumber==1) //menu d'acceuil
	{
		drawWall(maxX, maxY);
		textmenu();
	}
	if (mapnumber == 2 || mapnumber == 6) //lance une nouvelle game
	{
		drawWall(maxX, maxY);
		drawhp();
		
		if (li->starList != NULL || li->endList != NULL)
		{
		drawAllLines(li);
		}	
		drawEdges();
		if (e->starList != NULL || e->endList != NULL)
		{
		drawAllEnnemis(e);
		}	
		if (t->starList != NULL || t->endList != NULL)
		{
		drawAllTirs(t);
		}
		drawPlayer(p);
		moveplayer();
		drawScore();
		drawLife();
		drawBlueAmmo();
		drawAmmo();
		drawLevel();
		if (pauseingame==true)
		{
			drawPause();
		}
	}
	if ((mapnumber == 2 || mapnumber==6) && (p->life==0||p->score<0))
	{
		drawGameOver();
		drawChoiceinGame();
		checkCollisionplayerchoix(); //
	}
	if (mapnumber ==3)//charge la page de credits 
	{
		drawCredits(); 
	}
	if (mapnumber ==4)
	{
		drawOptions();
	}
	if (mapnumber ==5)
	{
		drawScores();
	}
	
	
	glutKeyboardFunc(Keyboard);  //fonction de glut gérant le clavier
	
	glutPostRedisplay();
}

void checkCollision (enemy e, tirsP r)
{	
	bool ColX = false;
	bool ColY = false;
	bool CHECKCOLLISION = false;
	if(e->pos.x <= r->pos.x+1 && e->pos.x+2 >=  r->pos.x)
	{
		ColX = true;
	}
	if(e->pos.y<=r->pos.y+0 && e->pos.y+1 >= r->pos.y )
	{
		ColY = true;
	}
	if(ColX && ColY)
	{
		CHECKCOLLISION = true;
	}
	if(CHECKCOLLISION)
	{
		if (e->life!=0)
		{
			if (r->color==1 )//passse a travers les ennemis ... mais ne les touche pas quand freez
			{
				if (e->life==1 || e->active==3)
				{
					e->life --;
					r->active = false;
					CHECKCOLLISION = false;
					ammo +=1;
					if (p->score>=700)
					{
						p->score += 20;  //incrémente le score de 10 apèrs chaque colliision entre un tir et un ennemi
					}
					if (p->score<700)
					{
						p->score += 10;
					}
				}
			}
			if (r->color==2)
			{
				r->active = false;
				CHECKCOLLISION = false;
				blueammo+=1;
				e->active=3;				
			}
		}
		if(e->life==0)
		{
			e->active=0;
		}
	}
} 

void checkCollisionplayer(enemy e)
{
	bool ColX = false;
	bool ColY = false;
	bool CHECKCOLLISION = false;
	if(e->pos.x <= p->pos.x+1 && e->pos.x+2 >=  p->pos.x)
	{
		ColX = true;
	}
	if(e->pos.y<=p->pos.y+1 && e->pos.y+1 >= p->pos.y )
	{
		ColY = true;
	}
	if(ColX && ColY)
	{
		CHECKCOLLISION = true;
	}
	if(CHECKCOLLISION)
	{
		if (e->life>0)
		{
			e->life -=3;
			CHECKCOLLISION = false;
			p->score += 5;  //incrémente le score de 5 apèrs chaque colliision entre un tir et un ennemi
			p->life --;
		} 
		if (e->life<=0)
		{
			e->active=0;
		}
	}
}


