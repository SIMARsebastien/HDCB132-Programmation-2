#ifndef _PLAYER_H_
#define _PLAYER_H_
extern int blueammo;
extern int ammo;
struct positionP
{
	int x;
	int y;
};

struct play
{
	struct positionP pos;
	int score;
	int life;
	bool weapon;
};

typedef struct play *player;
extern player p;

player createPlayer(int *maxX, int *maxY);
void moveLeft(player p);
void moveRight(player p);
void moveUp(player p);
void moveDown(player p);

#endif
