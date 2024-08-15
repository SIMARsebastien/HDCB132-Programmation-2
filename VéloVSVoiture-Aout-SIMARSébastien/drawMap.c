#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include "loadMap.h"
#include "drawMap.h"
#include "game.h"
#include "line.h"
#include "scores.h"
#include <string.h>

void drawSky()
{
        glBegin(GL_POLYGON); 
        glColor3f(0,0,0);
        glVertex3f(Square_size, 30*Square_size, 1);
        glVertex3f(Square_size, Square_size, 1);
        glVertex3f(30*Square_size, 0, 1);
        glVertex3f(30*Square_size, 30*Square_size, 1);
        glEnd();
}

void drawEdges() //couvrir le problème de bandes
{
  	glColor3f(0.0f,0.0f,0.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();//remet le pointeur 0,0 à 0,0 des le début.
		glTranslatef(25*Square_size,-1*Square_size,0.0f);

		glBegin(GL_QUADS);
		glColor3f(0.4,0.2,0);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(2*Square_size, 0.0f, 0.0f);
		glVertex3f(2*Square_size,2*Square_size, 0.0f);
		glVertex3f(0.0f,2*Square_size, 0.0f);

		glEnd();

	glColor3f(0.0f,0.0f,0.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();//remet le pointeur 0,0 à 0,0 des le début.
		glTranslatef(13*Square_size,-1*Square_size,0.0f);

		glBegin(GL_QUADS);
		glColor3f(0.4,0.2,0);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(2*Square_size, 0.0f, 0.0f);
		glVertex3f(2*Square_size,2*Square_size, 0.0f);
		glVertex3f(0.0f,2*Square_size, 0.0f);

		glEnd();
}

void drawWall(int *maxX, int *maxY)			// fonction qui affiche les murs et les plateformes
{	
	for (int j = 0; j < (*maxX); ++j)
	{
		for (int i = 0; i < (*maxY); ++i)
		{
			drawSky();
			if(*(*(map + j) + i) == '#')
			{
                glColor3f(1.0f,1.0f,1.0f);
				glMatrixMode(GL_MODELVIEW);
				
			    glLoadIdentity();
				glTranslatef(i*Square_size,j*Square_size,0.0f);
				glBegin(GL_QUADS);
				glColor3f(0.4,0.2,0);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(Square_size, 0.0f, 0.0f);
				glVertex3f(Square_size,Square_size, 0.0f);
				glVertex3f(0.0f,Square_size, 0.0f);

				glEnd();
			}
			if(*(*(map + j) + i) == '1' || *(*(map + j) + i) =='4')
			{
                glColor3f(1.0f,1.0f,1.0f);
				glMatrixMode(GL_MODELVIEW);
				
			    glLoadIdentity();
				glTranslatef(i*Square_size,j*Square_size,0.0f);
				glBegin(GL_QUADS);
				glColor3f(1.0,1,1);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(Square_size, 0.0f, 0.0f);
				glVertex3f(Square_size,Square_size, 0.0f);
				glVertex3f(0.0f,Square_size, 0.0f);

				glEnd();	
			}
			if(*(*(map + j) + i) == '2')
			{
                glColor3f(1.0f,1.0f,1.0f);
				glMatrixMode(GL_MODELVIEW);
				
			    glLoadIdentity();
				glTranslatef(i*Square_size,j*Square_size,0.0f);
				glBegin(GL_QUADS);
				glColor3f(0,1,0);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(Square_size, 0.0f, 0.0f);
				glVertex3f(Square_size,Square_size, 0.0f);
				glVertex3f(0.0f,Square_size, 0.0f);

				glEnd();	
			}
			if(*(*(map + j) + i) == '0')
			{
                glColor3f(1.0f,1.0f,1.0f);
				glMatrixMode(GL_MODELVIEW);
				
			    glLoadIdentity();
				glTranslatef(i*Square_size,j*Square_size,0.0f);
				glBegin(GL_QUADS);
				glColor3f(0,1,0);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(Square_size, 0.0f, 0.0f);
				glVertex3f(Square_size,Square_size, 0.0f);
				glVertex3f(0.0f,Square_size, 0.0f);

				glEnd();	
			}
		}
	}
}

void drawPlayer(player p)
{
	int i, j;
	i = p->pos.x;
	j = p->pos.y;
	
	glColor3f(0.0f,0.5f,0.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(j*Square_size,i*Square_size,0.0f);

	glBegin(GL_QUADS);

	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(2*Square_size, 0.0f, 0.0f);
	glVertex3f(2*Square_size,2*Square_size, 0.0f);
	glVertex3f(0.0f,2*Square_size, 0.0f);
	//glBegin(GL_TRIANGLES); //pour faireun triangle à la place du carré . (pour représenter le joueur)
	//glColor3f(0.0f,0.5f,0.0f);
	//glVertex2f(-2*Square_size, 0.0f);
	//glVertex2f(0,2*Square_size);
	//glVertex2f(0.0f,0);
	glEnd(); 
}

void drawEnemy(enemy e)	
{
	int i, j;
	i = e->pos.x;
	j = e->pos.y;
	
		if (e->life==1 && e->active!=3) 
		{
			glColor3f(1.0f,0.0f,0.0f);
		}
		if (e->active==3)
		{
			glColor3f(0.0f,0.0f,1.0f);
		}
		if ((e->life == 2 || e->life==3)&&e->active!=3)
		{
			glColor3f(0.8f,0.6f,0.8f);
		}
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	/*unsigned int texture; // test de texture mais non concluant car 3 images en décalé au lieu d'une seul fixe et également surchauffe pc
	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	gluBuild2DMipmaps(GL_TEXTURE_2D,moto1.bytes_per_pixel, moto1.width, moto1.height,GL_RGB,GL_UNSIGNED_BYTE,moto1.pixel_data);
	glEnable(GL_TEXTURE_2D);*/
	
	glTranslatef(j*Square_size,i*Square_size,0.0f);
	glBegin(GL_QUADS); 
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(2*Square_size,0.0f,0.0f);
	glVertex3f(2*Square_size,2*Square_size,0.0f);
	glVertex3f(0.0f,2*Square_size,0.0f);
	glEnd();	
}

void drawTirs(tirsP t)
{
	if (t->color==1) //compare la couleur de toutes les  balles et ci elle est égale à 1, la balle sera de couleur jaune
	{
		int i, j;
		i = t->pos.x;
		j = t->pos.y;
		glColor3f(1.0f, 1.0f, 0.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(j*Square_size,i*Square_size,0.0f);
		glBegin(GL_QUADS);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(Shoot_size,0.0f,0.0f);
		glVertex3f(Shoot_size,Shoot_size,0.0f);
		glVertex3f(0.0f,Shoot_size,0.0f);
		glEnd();
	}
	if (t->color==2) //compare la couleur de toutes les  balles et ci elle est égale à 2, la balle sera de couleur bleu
	{
		int i, j;
		i = t->pos.x;
		j = t->pos.y;
		glColor3f(0.0f, 0.0f, 1.0f); 
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(j*Square_size,i*Square_size,0.0f);
		glBegin(GL_QUADS);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(2*Shoot_size,0.0f,0.0f);
		glVertex3f(2*Shoot_size,2*Shoot_size,0.0f);
		glVertex3f(0.0f,2*Shoot_size,0.0f);
		glEnd();
	}
}

void drawAllEnnemis(listeEn e)
{	
	enemy first = malloc(sizeof(enemies));
	enemy next = malloc(sizeof(enemies));
	first = e->starList;
	next = e->starList->nextptr;
	if (e->starList != NULL || e->endList != NULL)
	{
		drawEnemy(first);
		if (e->starList->nextptr != NULL)
		{
			drawEnemy(next);
			while (next->nextptr != NULL)
			{
				next = next->nextptr;
				drawEnemy(next);
			}
		}
	}
}

void drawAllTirs(listetirsP t)
{
	tirsP first = malloc(sizeof(tirs));
	tirsP next = malloc(sizeof(tirs));
	first = t->starList;
	if (t->starList != NULL && t->starList->nextptr != NULL)
	{
	next = t->starList->nextptr;
	}
	if (t->starList != NULL || t->endList != NULL)
	{
		drawTirs(first);
		if (t->starList->nextptr != NULL)
		{
			drawTirs(next);
			while (next->nextptr != NULL)
			{
				next = next->nextptr;
				drawTirs(next);
			}
		}
	}
}

void drawLines(line l) //
{
	int i, j;
	i = l->pos.x;
	j = l->pos.y;
	
	glColor3f(1.0f,1.0f,1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(j*Square_size,i*Square_size,0.0f);

	glBegin(GL_QUADS);

	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(Square_size, 0.0f, 0.0f);
	glVertex3f(Square_size,Square_size, 0.0f);
	glVertex3f(0.0f,Square_size, 0.0f);

	glEnd();
}

void drawAllLines (listeLi li)
{
	line first = malloc(sizeof(lines));
	line next = malloc(sizeof(lines));
	first = li->starList;
	if (li->starList != NULL && li->starList->nextptr != NULL)
	{
	next = li->starList->nextptr;
	}
	if (li->starList != NULL || li->endList != NULL)
	{
		drawLines(first);
		if (li->starList->nextptr != NULL)
		{
			drawLines(next);
			while (next->nextptr != NULL)
			{
				next = next->nextptr;
				drawLines(next);
			}
		}
	}
}

void vStrokeOutput(GLfloat x, GLfloat y, char *string, void *font)//test pour écrire en plus gros 
{
	char *p;
	glPushMatrix();	// glPushMatrix et glPopMatrix sont utilisées pour sauvegarder 
			// et restaurer les systèmes de coordonnées non translatés
	glTranslatef(x, y,0); // Positionne le premier caractère de la chaîne
	for (p = string; *p; p++) glutStrokeCharacter(font, *p); // Affiche chaque caractère de la chaîne
	glPopMatrix();
}

void vBitmapOutput(int x, int y, char *string, void *font)// fonction pour écrire les textes
{
	int len,i; // len donne la longueur de la chaîne de caractères
	glRasterPos2f(x,y); // Positionne le premier caractère de la chaîne
	len = (int) strlen(string); // Calcule la longueur de la chaîne
	for (i = 0; i < len; i++) glutBitmapCharacter(font,string[i]); // Affiche chaque caractère de la chaîne
}

void textmenu() //fonction qui gere l'affichage du menu principal (la couleur du texte change si la souris est placée sur la zone de text)
{ 
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0*Square_size,0*Square_size,0.0f);

		if (idleMouseX>294 && idleMouseX<482 &&	idleMouseY>135 && idleMouseY<155)
		{
			glColor3d(1,1,1);
		}
		else
		{
			glColor3d(1,0,0); //rouge		
		}
		vBitmapOutput(300,150,"NEW GAME",GLUT_BITMAP_HELVETICA_18);

		if (idleMouseX>294 && idleMouseX<439 && idleMouseY>181&& idleMouseY<205)
		{
			glColor3d(1,1,1);
		}
		else
		{
			glColor3d(1,0.65,0); // orange vif		
		}		
		vBitmapOutput(300,200,"LOAD GAME",GLUT_BITMAP_HELVETICA_18);

		if (idleMouseX>294 && idleMouseX<455 && idleMouseY>233&& idleMouseY<255)//si bouton choix nom player
		{
			glColor3d(1,1,1);
		}
		else
		{
			glColor3d(1,0.65,0); // orange vif
		}	
		vBitmapOutput(300,250,"PLAYER NAME",GLUT_BITMAP_HELVETICA_18);

		if (idleMouseX>294 && idleMouseX<421 && idleMouseY>333&& idleMouseY<355)//si bouton scores
		{
			glColor3d(1,1,1);
		}
		else
		{
			glColor3d(1,1,0); // jaune
		}	
		vBitmapOutput(300,350,"SCORES",GLUT_BITMAP_HELVETICA_18);
		
		if (idleMouseX>294 && idleMouseX<421 && idleMouseY>386&& idleMouseY<406)
		{
			glColor3d(1,1,1);
		}
		else
		{
			glColor3d(1,1,0);
		}		
		vBitmapOutput(300, 400, "OPTIONS (O)",GLUT_BITMAP_HELVETICA_18);

		glColor3d(0.6,0.6,0.6); // Texte en gris
		vBitmapOutput(620, 570, "2024.Credits(C)",GLUT_BITMAP_TIMES_ROMAN_24);
		vBitmapOutput(10, 30, "EXIT (ESC)",GLUT_BITMAP_TIMES_ROMAN_24);
	}

void drawScore()//afficher le score du joueur
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0*Square_size,0*Square_size,0.0f);

	static char textScore[50];
	int score = p->score;
	sprintf(textScore, "Score : %i", score);

    char *s=textScore;
	glColor3d(1,1,1); 
	vBitmapOutput(5,15,s,GLUT_BITMAP_HELVETICA_18);
}

void drawLife()//afficher la vie du joueur
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0*Square_size,0*Square_size,0.0f);

	static char textLife[50];
	sprintf(textLife, "Life"); //: %i", life); // mettre trois carrés avec texture "coeur" à la place d'un compteur.
    char *s=textLife;
	glColor3d(1,1,1); // Texte en blanc
	vBitmapOutput(50,40,s,GLUT_BITMAP_HELVETICA_18);//(120,15,s,GLUT_BITMAP_HELVETICA_18);
}

void drawBlueAmmo()//afficher le nombre de balles ralentisseuses
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0*Square_size,0*Square_size,0.0f);

	static char textblueammo[50];
	sprintf(textblueammo, "Ammo : %i", blueammo); // mettre trois carrés avec texture "coeur" à la place d'un compteur.
    char *s=textblueammo;
	glColor3d(0,0,1); // Texte en bleu
	vBitmapOutput(305,15,s,GLUT_BITMAP_HELVETICA_18);
}

void drawAmmo()//afficher le nombre de balles 
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0*Square_size,0*Square_size,0.0f);

	static char textammo[50];
	sprintf(textammo, "Ammo : %i", ammo); // mettre trois carrés avec texture "coeur" à la place d'un compteur.
    char *s=textammo;
	glColor3d(1,1,0); // Texte en jaune
	vBitmapOutput(205,15,s,GLUT_BITMAP_HELVETICA_18);
}

void drawName()//afficher le nom du player
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0*Square_size,0*Square_size,0.0f);

	static char textname[50];
	sprintf(textname, "Player : %s", playernamearray); // mettre trois carrés avec texture "coeur" à la place d'un compteur.
    char *s=textname;
	glColor3d(1,1,1); // Texte en jaune
	vBitmapOutput(410,15,s,GLUT_BITMAP_HELVETICA_18);
}

void drawGameOver() //afficher le menu "game over"
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0*Square_size,0*Square_size,0.0f);

	glColor3d(1,0,0); // Texte en rouge
	vBitmapOutput(330,320,"GAME-OVER!!",GLUT_BITMAP_HELVETICA_18);
}

void drawPause()//affiche le menu pause // to do:// rajouter (save/exit/load/restart/options/...)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0*Square_size,0*Square_size,0.0f);

	static char textammo[50];
	sprintf(textammo, "PAUSE"); 
    char *s=textammo;
	glColor3d(1,0,0); // Texte en rouge
	vBitmapOutput(360,320,s,GLUT_BITMAP_HELVETICA_18);
	glColor3d(0,0,0); // Texte en rouge
	vBitmapOutput(10,450,"SAVE(S)",GLUT_BITMAP_HELVETICA_18); 
	vBitmapOutput(10,475,"LOAD(L)",GLUT_BITMAP_HELVETICA_18);
	vBitmapOutput(10,425,"MAIN MENU(M)",GLUT_BITMAP_HELVETICA_18);
	vBitmapOutput(10,500,"RESTART(N)",GLUT_BITMAP_HELVETICA_18);
	vBitmapOutput(10,525,"COMMANDES(O)",GLUT_BITMAP_HELVETICA_18);
}

void drawChoiceinGame()
{
	glColor3f(0.0f,0.0f,0.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glTranslatef(0*Square_size,0*Square_size,0.0f);

	glBegin(GL_QUADS);//rectangle noir en haut a gauche
	glVertex3f(10.0f,25.0f,0.0f);
	glVertex3f(110,25.0f,0.0f);
	glVertex3f(110,75,0.0f);
	glVertex3f(10.0f,75,0.0f);
	glEnd();

		glBegin(GL_QUADS); //haut droite
	glVertex3f(670,25,0.0f);
	glVertex3f(770.0f,25,0.0f);
	glVertex3f(770.0f,75,0.0f);
	glVertex3f(670.0f,75,0.0f);
	glEnd();

		glBegin(GL_QUADS);//bas gauche
	glVertex3f(10.0f,490.0f,0.0f);
	glVertex3f(110,490.0f,0.0f);
	glVertex3f(110,540,0.0f);
	glVertex3f(10.0f,540,0.0f);
	glEnd();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0*Square_size,0*Square_size,0.0f);

	glColor3d(1,1,1); // Texte en blanc
	vBitmapOutput(35,60,"MENU",GLUT_BITMAP_HELVETICA_18); 
	vBitmapOutput(680,50,"LOAD",GLUT_BITMAP_HELVETICA_18);
	vBitmapOutput(690,70,"GAME",GLUT_BITMAP_HELVETICA_18);
	vBitmapOutput(20,520,"RESTART",GLUT_BITMAP_HELVETICA_18);
	static char textscore[50];
	sprintf(textscore, "SCORE: %d",p->score); 
    char *k=textscore;
	glColor3d(0,0,0); // Texte en noir
	vBitmapOutput(665,500,k,GLUT_BITMAP_HELVETICA_18); //(premiere valeur = vers la droite deuxieme egale deplacement vers le bas
}

void drawtextacceuil()//dessine la première page
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0*Square_size,0*Square_size,0.0f);
	glColor3d(186.0f/255.0f,85.0f/255.0f,211.0f/255.0f); // Texte en Mauve
	
	vBitmapOutput(250,60,"Bienvenue dans BIKE KILLER!!!",GLUT_BITMAP_HELVETICA_18);

	static char textbestscore[50];
	sprintf(textbestscore, "Meilleur score: %d realise par: %s",tabScores[0],tabNamesScores[0]); 
    char *k=textbestscore;
	//glColor3d(0,0,0); // Texte en noir
	vBitmapOutput(240,400,k,GLUT_BITMAP_HELVETICA_18); 
	

	glColor3d(1,1,1); // Texte en blanc
	vBitmapOutput(260,500,"(PRESS 'SPACE' TO START )",GLUT_BITMAP_HELVETICA_18); 
}

void drawChooseName()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0*Square_size,0*Square_size,0.0f);
	glColor3d(186.0f/255.0f,85.0f/255.0f,211.0f/255.0f); // Texte en Mauve
	
	vBitmapOutput(300,100,"Enter your name:",GLUT_BITMAP_HELVETICA_18);

	static char pname[50];
	sprintf(pname, "name: %s",playernamearray); 
    char *k=pname;
	glColor3d(1,1,1);
	vBitmapOutput(250,300,k,GLUT_BITMAP_HELVETICA_18); 
	glColor3d(1,1,1); // Texte en blanc
	vBitmapOutput(260,500,"(press 'ENTER' to confirm!)",GLUT_BITMAP_HELVETICA_18); 
}

void drawCredits() //dessine la page des crédits
{
	if (mapnumber==3)
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0*Square_size,0*Square_size,0.0f);

		glColor3d(1,1,1); // Texte en blanc
		vBitmapOutput(35,60,"Jeu réalise dans le cadre du cours de programmation 2: IHDCB132",GLUT_BITMAP_HELVETICA_18);
		vBitmapOutput(35,120,"Professeur responssable: JAMES JERSON ORTIZ VEGA",GLUT_BITMAP_HELVETICA_18);
		vBitmapOutput(35,180,"Jeu realiser par:SIMAR SEBASTIEN",GLUT_BITMAP_HELVETICA_18);
		vBitmapOutput(35,240,"Remerciements: un tout grand merci a Francois SIMAR pour son aide apportee",GLUT_BITMAP_HELVETICA_18);
		vBitmapOutput(35,300,"Merci egalement a ma compagne de m'avoir fournit le temps necessaire pour ce travail.",GLUT_BITMAP_HELVETICA_18);
	}
}

void drawOptions()//dessine la page options
{
	if (mapnumber==4)
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0*Square_size,0*Square_size,0.0f);

		glColor3d(1,1,1); // Texte en blanc
		vBitmapOutput(45,40,"COMMANDES ",GLUT_BITMAP_HELVETICA_18);
		vBitmapOutput(35,120,"Gauche : Q or left arrow",GLUT_BITMAP_HELVETICA_18);
		vBitmapOutput(35,180,"Droite : D or right arrow",GLUT_BITMAP_HELVETICA_18);
		vBitmapOutput(35,240,"Haut: Z or up arrow",GLUT_BITMAP_HELVETICA_18);
		vBitmapOutput(35,300,"Bas : S or down arrow",GLUT_BITMAP_HELVETICA_18);
		vBitmapOutput(35,360,"Tirer : (space-bar)",GLUT_BITMAP_HELVETICA_18);
		vBitmapOutput(35,420,"Change weapon : E",GLUT_BITMAP_HELVETICA_18);
		vBitmapOutput(35,480,"Pause : (Esc)",GLUT_BITMAP_HELVETICA_18);
		vBitmapOutput(350,130,"Ennemi basique: 1HP",GLUT_BITMAP_HELVETICA_18);
		vBitmapOutput(350,230,"Ennemi with shield: 1hp+2h shield(need to be freeze)",GLUT_BITMAP_HELVETICA_18);
		vBitmapOutput(350,330,"Ennemi freez",GLUT_BITMAP_HELVETICA_18);
		vBitmapOutput(350,430,"Player",GLUT_BITMAP_HELVETICA_18);
		vBitmapOutput(350,550,"Classique ammo",GLUT_BITMAP_HELVETICA_18);
		vBitmapOutput(550,550,"Frezz ammo",GLUT_BITMAP_HELVETICA_18);

			glColor3f(1.0f,0.0f,0.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();//remet le pointeur 0,0 à 0,0 des le début.
		glTranslatef(15*Square_size,5*Square_size,0.0f);

		glBegin(GL_QUADS);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(2*Square_size, 0.0f, 0.0f);
		glVertex3f(2*Square_size,2*Square_size, 0.0f);
		glVertex3f(0.0f,2*Square_size, 0.0f);
		glEnd();

			glColor3f(0.8,0.6,0.8);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(15*Square_size,10*Square_size,0.0f);

		glBegin(GL_QUADS);
		glVertex3f(0,0,0);
		glVertex3f(2*Square_size, 0.0f, 0.0f);
		glVertex3f(2*Square_size,2*Square_size, 0.0f);
		glVertex3f(0.0f,2*Square_size, 0.0f);
		glEnd();

			glColor3f(0,0,1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(15*Square_size,15*Square_size,0.0f);

		glBegin(GL_QUADS);
		glVertex3f(0,0,0);
		glVertex3f(2*Square_size, 0.0f, 0.0f);
		glVertex3f(2*Square_size,2*Square_size, 0.0f);
		glVertex3f(0.0f,2*Square_size, 0.0f);
		glEnd();

			glColor3f(0,0.5,0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(15*Square_size,20*Square_size,0.0f);

		glBegin(GL_QUADS);
		glVertex3f(0,0,0);
		glVertex3f(2*Square_size, 0.0f, 0.0f);
		glVertex3f(2*Square_size,2*Square_size, 0.0f);
		glVertex3f(0.0f,2*Square_size, 0.0f);
		glEnd();

			glColor3f(1.0f, 1.0f, 0.0f); //draw tir classique
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(16*Square_size,27*Square_size,0.0f);

		glBegin(GL_QUADS);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(Shoot_size,0.0f,0.0f);
		glVertex3f(Shoot_size,Shoot_size,0.0f);
		glVertex3f(0.0f,Shoot_size,0.0f);
		glEnd();

			glColor3f(0.0f, 0.0f, 1.0f); //draw tir freez
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(26*Square_size,27*Square_size,0.0f);

		glBegin(GL_QUADS);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(2*Shoot_size,0.0f,0.0f);
		glVertex3f(2*Shoot_size,2*Shoot_size,0.0f);
		glVertex3f(0.0f,2*Shoot_size,0.0f);
		glEnd();
	}
}

void drawhp()//sert à dessiner les point de vies du joueur. 
{
	if (p->life!=0)
	{
		glColor3f(1,0.41,0.71);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(1*Square_size,2*Square_size,0.0f);
		
		glBegin(GL_QUADS);

		glVertex3f(0,0,0);
		glVertex3f(Square_size, 0.0f, 0.0f);
		glVertex3f(Square_size,Square_size, 0.0f);
		glVertex3f(0.0f,Square_size, 0.0f);

		glEnd();
	}
	if (p->life>1)
	{
		glColor3f(1,0.41,0.71);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(3*Square_size,2*Square_size,0.0f);
		
		glBegin(GL_QUADS);

		glVertex3f(0,0,0);
		glVertex3f(Square_size, 0.0f, 0.0f);
		glVertex3f(Square_size,Square_size, 0.0f);
		glVertex3f(0.0f,Square_size, 0.0f);

		glEnd();
	}
	if (p->life>2)
	{
		glColor3f(1,0.41,0.71);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(5*Square_size,2*Square_size,0.0f);
		
		glBegin(GL_QUADS);

		glVertex3f(0,0,0);
		glVertex3f(Square_size, 0.0f, 0.0f);
		glVertex3f(Square_size,Square_size, 0.0f);
		glVertex3f(0.0f,Square_size, 0.0f);

		glEnd();
	}	
}

void drawLevel() //gere l'affichage des infos selon le niveau de jeu actuel
{
	if (level==1)
	{
		timerNewEnnemis=3000;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0*Square_size,0*Square_size,0.0f);

		glColor3d(1,1,1); // Texte en blanc
		vBitmapOutput(660,40,"LEVEL: 1 ",GLUT_BITMAP_HELVETICA_18);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0*Square_size,0*Square_size,0.0f);
		static char textScore[50];
		int score = p->score;
		sprintf(textScore, "%i/100", score);

		char *s=textScore;
		glColor3d(1,1,1); // Texte en blanc
		vBitmapOutput(660,60,s,GLUT_BITMAP_HELVETICA_18);
		if (p->score==100)
		{
			level=2;
		}	
	}
	if (level==2)
	{
		timerNewEnnemis=2000;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0*Square_size,0*Square_size,0.0f);

		glColor3d(1,1,1); // Texte en blanc
		vBitmapOutput(660,40,"LEVEL: 2 ",GLUT_BITMAP_HELVETICA_18);
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0*Square_size,0*Square_size,0.0f);
		static char textScore[50];
		int score2 = p->score-100;
		sprintf(textScore, "%i/200", score2);

		char *s=textScore;
		glColor3d(1,1,1); // Texte en blanc
		vBitmapOutput(660,60,s,GLUT_BITMAP_HELVETICA_18);
		if (p->score==300)
		{
			level=3;
		}
	}
	if (level==3)
	{
		timerNewEnnemis=2000;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0*Square_size,0*Square_size,0.0f);

		glColor3d(1,1,1); // Texte en blanc
		vBitmapOutput(660,40,"LEVEL: 3 ",GLUT_BITMAP_HELVETICA_18);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0*Square_size,0*Square_size,0.0f);
		static char textScore[50];
		int score3 = p->score-300;
		sprintf(textScore, "%i/400", score3);

		char *s=textScore;
		glColor3d(1,1,1); // Texte en blanc
		vBitmapOutput(660,60,s,GLUT_BITMAP_HELVETICA_18);
		if (p->score==700)
		{
			level=4;
		}
	}
	if (level==4)
	{
		timerNewEnnemis=1500;
		//ennemisdeplacement
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0*Square_size,0*Square_size,0.0f);

		glColor3d(1,1,1); // Texte en blanc
		vBitmapOutput(660,40,"LEVEL: 4 ",GLUT_BITMAP_HELVETICA_18);
		vBitmapOutput(660,80,"POINTSx2 ",GLUT_BITMAP_HELVETICA_18);
		glLoadIdentity();
		glTranslatef(0*Square_size,0*Square_size,0.0f);
		static char textScore[50];
		sprintf(textScore, "%i", p->score);

		char *s=textScore;
		glColor3d(1,1,1); // Texte en blanc
		vBitmapOutput(660,60,s,GLUT_BITMAP_HELVETICA_18);
	}
}

void drawScores() // dessine les scores des 5 meilleurs joueurs.
{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0*Square_size,0*Square_size,0.0f);
		static char textScore1[50];
		static char textScore2[50];
		static char textScore3[50];
		static char textScore4[50];
		static char textScore5[50];
		glColor3d(1,1,1); // Texte en blanc
		vBitmapOutput(310,65,"SCORES ",GLUT_BITMAP_HELVETICA_18);

		sprintf(textScore1, "1 : %s : %i",tabNamesScores[0],tabScores[0]);
		char *s1=textScore1;
		glColor3d(1,1,1); // Texte en blanc
		vBitmapOutput(300,100,s1,GLUT_BITMAP_HELVETICA_18);

		sprintf(textScore2, "2 : %s : %i",tabNamesScores[1],tabScores[1]);
		char *s2=textScore2;
		glColor3d(1,1,1); // Texte en blanc
		vBitmapOutput(300,135,s2,GLUT_BITMAP_HELVETICA_18);

		sprintf(textScore3, "3 : %s : %i",tabNamesScores[2],tabScores[2]);
		char *s3=textScore3;
		glColor3d(1,1,1); // Texte en blanc
		vBitmapOutput(300,170,s3,GLUT_BITMAP_HELVETICA_18);

		sprintf(textScore4, "4 : %s : %i",tabNamesScores[3],tabScores[3]);
		char *s4=textScore4;
		glColor3d(1,1,1); // Texte en blanc
		vBitmapOutput(300,205,s4,GLUT_BITMAP_HELVETICA_18);

		sprintf(textScore5, "5 : %s : %i",tabNamesScores[4],tabScores[4]);
		char *s5=textScore5;
		glColor3d(1,1,1); // Texte en blanc
		vBitmapOutput(300,240,s5,GLUT_BITMAP_HELVETICA_18);
}