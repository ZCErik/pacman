#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "PacMan.h"
#include "Map.h"
#include "ui.h"

MAP map;
POSITION hero;

int hasPill = 0;

int ghostPath(int xnow, int ynow, 
	int* xdestination, int* ydestination){

	int options[4][2] = {
		{xnow, ynow +1},
		{xnow +1, ynow},
		{xnow, ynow -1},
		{xnow -1, ynow}
	};

	srand(time(0));

	for(int i = 0; i < 10; i++){
		int position = rand() % 4;

		if (walk(&map, GHOST, options[position][0], options[position][1])) {
			*xdestination = options[position][0];
			*ydestination = options[position][1];

			return 1;
		}
	}

	return 0;
}

void ghosts(){
	MAP copy;

	copyMap(&copy, &map);

	for(int i = 0; i < map.lines; i++){
		for(int j = 0; j < map.columns; j++){

			if(copy.matriz[i][j] == GHOST){

				int xgo;
				int ygo;

				int find = ghostPath(i, j,
					&xgo, &ygo);


				if(find){
					walkMap(&map, i, j, xgo, ygo);
				}
			}
		}
	}

	freeMap(&copy);
}

int endGame() {
	POSITION pos;

	int lost = !findMap(&map, &pos, HERO);
	int win = !findMap(&map, &pos, GHOST);

	return win || lost;
}

int isDirection(char direction){
	return direction == 'a' ||
		   direction == 'w' ||
		   direction == 's' ||
		   direction == 'd';
}

void move(char direction) {

	if(!isDirection(direction))
		return;

	int nextX = hero.x;
	int nextY = hero.y;

	switch (direction){
		case LEFT:
			nextY--;
			break;
		case UP:
			nextX--;
			break;
		case DOWN:
			nextX++;
			break;
		case RIGHT:
			nextY++;
			break;
	}

	if(!walk(&map, HERO, nextX, nextY))
		return;

	if(isCharacter(&map, PILL, nextX, nextY)){
		hasPill = 1;
	}

	walkMap(&map, hero.x, hero.y, nextX, nextY);

	hero.x = nextX;
	hero.y = nextY;

}

void explodePill(){

	if(!hasPill) return;

	explodePill2(hero.x, hero.y, 0, 1, 3);
	explodePill2(hero.x, hero.y, 0, -1, 3);
	explodePill2(hero.x, hero.y, 1, 0, 3);
	explodePill2(hero.x, hero.y, -1, 0, 3);

	hasPill = 0;
}

void explodePill2(int x, int y, int sumx, int sumy, int qt){
	
	if(qt == 0) return;

	int newx = x + sumx;
	int newy = y + sumy;

	if(!valid(&map, newx, newy)) return;
	if(wall(&map, newx, newy)) return;

	map.matriz[newx][newy] = EMPTY;
	explodePill2(newx, newy, sumy, sumx, qt - 1);
}

int main() {
	
	readMap(&map);
	findMap(&map, &hero, HERO);

	do {
		printf("Has pill: %s\n", (hasPill ? "Yes" : "No"));
		printMap(&map);

		char command;

		scanf(" %c", &command);
		move(command);
		
		if(command == BOMB) {
			explodePill();
		}

		ghosts(); 

	} while (!endGame());
	
	freeMap(&map);

	return 0;
} 

