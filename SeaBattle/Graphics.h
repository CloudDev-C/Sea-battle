#pragma once
#include <iostream>
#include <Windows.h>
#include "Ships.h"
#include "Game.h"

void Draw(HANDLE hConsole);
void DrawShips(Players player, COORD coord);
void DrawOneArea(HANDLE hConsole, COORD coord, Players player);
void DrawInfo(HANDLE hConsole);

extern char Letters[SIZE_AREA];
