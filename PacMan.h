#ifndef _PACMAN_H_
#define _PACMAN_H_

#define UP 'w'
#define DOWN 's'
#define RIGHT 'd'
#define LEFT 'a'
#define BOMB 'b'

void move(char direction);
int endGame();
int isDirection(char direction);
void ghosts();
int ghostPath(int xnow, int ynow, 
	int* xdestination, int* ydestination);

void explodePill();

void explodePill2(int x, int y, int sumx, int sumy, int qt);

#endif