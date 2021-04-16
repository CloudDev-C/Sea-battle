#pragma once
#include <Windows.h>

#define SIZE_AREA 10
#define SHIPS_COUNT 10

struct Ship
{
	COORD *ship;
	int shipSize;
	int Killcount;
	bool orient;
};

extern int ShipsSize[SHIPS_COUNT];
