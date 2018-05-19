#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Map.h"

void copyMap(MAP* destination, MAP* origin){
	destination->lines = origin->lines;
	destination->columns = origin->columns;

	allocMap(destination);
	for(int i = 0; i < origin->lines; i++){
		strcpy(destination->matriz[i], origin->matriz[i]);
	}
}

void walkMap(MAP* map, int xorigin, int yorigin, 
			int xdestination, int ydestination){

	char character = map->matriz[xorigin][yorigin];
	map->matriz[xdestination][ydestination] = character;
	map->matriz[xorigin][yorigin] = EMPTY;
}

int valid(MAP* map, int x, int y){
	if(x >= map->lines)
		return 0;
	if(y >= map->columns)
		return 0;

	return 1;
}

int empty(MAP* map, int x, int y){
	return map->matriz[x][y] == EMPTY;
}

int findMap(MAP* map, POSITION* p, char c){
	int i; 
	int j;
	for (i = 0; i < map->lines; i++) {
		for (j = 0; j < map->columns; j++) {
			if (map->matriz[i][j] == c){
				p->x = i;
				p->y = j;
				return 1;
			}
		}
	}

	return 0;
}

int wall(MAP* map, int x, int y){
	return map->matriz[x][y] == VERTICAL_WALL ||
		map->matriz[x][y] == HORIZONTAL_WALL;
}

int isCharacter(MAP* map, char character, int x, int y){
	return map->matriz[x][y] == character;
}

int walk(MAP* map, char character, int x, int y){
	return
		valid(map, x, y) &&
		!wall(map, x, y) &&
		!isCharacter(map, character, x, y);
}


void freeMap(MAP* map) {

	int i;
	for (i = 0; i < map->lines; i++) {
		free(map->matriz[i]);
	}
	free(map->matriz);
}

void allocMap(MAP* map) {
	map->matriz = malloc(sizeof(char*) * map->lines);
	int i;
	for (i = 0; i < map->lines; i++) {
		map->matriz[i] = malloc(sizeof(char) * map->columns + 1);
	}
}

void readMap(MAP* map) {
	FILE *fp;

	fp = fopen("map.txt", "r");

	if (fp == 0) {
		printf("Map not found!");
		exit(1);
	}

	fscanf(fp, "%d" "%d", &(map->lines), &(map->columns));

	allocMap(map);

	int i;
	for (i = 0; i < 5; i++) {
		fscanf(fp, "%s", map->matriz[i]);
	}

	fclose(fp);
}
