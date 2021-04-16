#pragma once
#include "Game.h"
#include "Ships.h"
#include <vector>
#include <iostream>

enum GameStady
{
	ADDSHIPS = 0,
	GAMEPROCESS,
	GAMEEND
};

enum Players
{
	USER = 0,
	COMPUTER
};

struct GameData
{
	Ship *UserShips;
	Ship *CompShips;
	int UserShipCount;
	GameStady thisGame;
	bool Walk;
	//----
	int mode = 0;
	int X = 0;
	int Y = 0;
	int firstHitX = 0;
	int firstHitY = 0;
	int dir = 0;
	std::vector <int> dirs;
};

extern int UserArea[SIZE_AREA][SIZE_AREA];
extern int CompArea[SIZE_AREA][SIZE_AREA];

void GameInit();
void GameFreeMemory();
BOOL CheckArea(Ship ship_t, Players player, int X, int Y, bool orient);
void AddShip(bool orientation, int X, int Y);
void ComputerStep();
int GetShipID(Players player, int X, int Y);
bool CheckKillShip(Ship ship_);
void SetShipKill(Ship ship_, Players player);
bool CheckAllKill(Players player);

extern GameData sGame;