#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "Map.h"

char printWall[4][7] = {
    {"......" },
    {"......" },
    {"......" },
    {"......" }
};


char printHero[4][7] = {
    {" .--. "  },
    {"/ _.-'"  },
    {"\\  '-." },
    {" '--' "  }
};

char printPill[4][7] = {
    {"      "},
    {" .-.  "},
    {" '-'  "},
    {"      "}
};

char printEmpty[4][7] = {
    {"      "},
    {"      "},
    {"      "},
    {"      "}
};

char printGhost[4][7] = {
	{" .-.  " },
	{"| OO| " },
	{"|   | " },
	{"'^^^' " }
};

void printPart(char screen[4][7], int part){
	printf("%s", screen[part]);
}


void printMap(MAP* map) {
	
	for (int i = 0; i < map->lines; i++) {

		for(int part = 0; part < 4; part++){

			for (int j = 0; j < map->columns; ++j){

				switch(map->matriz[i][j]){
					case GHOST:
						printPart(printGhost, part);
						break;

					case HERO:
						printPart(printHero, part);
						break;

					case PILL:
						printPart(printPill, part);
						break;

					case VERTICAL_WALL:
					case HORIZONTAL_WALL:
						printPart(printWall, part);
						break;

					case EMPTY:
						printPart(printEmpty, part);
						break;
				}
				
			}

			printf("\n");
		}
	}
}

