#ifndef _MAP_H_
#define _MAP_H_

#define GHOST 'F'
#define HERO '@'
#define EMPTY '.'
#define VERTICAL_WALL '|'
#define HORIZONTAL_WALL '-'
#define PILL 'P'

struct Map {
	char** matriz;
	int lines;
	int columns;
};

typedef struct Map MAP;	

struct position {
	int x;
	int y;
};

typedef struct position POSITION;

int findMap(MAP* map, POSITION* p, char c);
void allocMap(MAP* map);
void readMap(MAP* map);
void freeMap(MAP* map);

int valid(MAP* map, int x, int y);
int empty(MAP* map, int x, int y);

void walkMap(MAP* map, int xorigin, int yorigin, 
			int xdestination, int ydestination);

void copyMap(MAP* destination, MAP* origin);

int walk(MAP* map, char character, int x, int y);

int wall(MAP* map, int x, int y);

int isCharacter(MAP* map, char character, int x, int y);

#endif