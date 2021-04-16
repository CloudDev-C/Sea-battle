#include "Control.h"
#include <iostream>

int Control(GameStady stady)
{
	HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);

	SetConsoleMode(hConsole, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);

	COORD coords;
	const int events_count = 256;
	INPUT_RECORD all_events[events_count];
	DWORD read_event;

	ReadConsoleInput(hConsole, all_events, events_count, &read_event);

	for (int i = 0; i < read_event; i++)
	{
		//------------------------------------------------------------
		coords.X = all_events[i].Event.MouseEvent.dwMousePosition.X;
		coords.Y = all_events[i].Event.MouseEvent.dwMousePosition.Y;

		if (all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			if (stady == GameStady::ADDSHIPS)
			{
				coords = CalcCoords(coords);

				if (coords.X >= 0 && coords.X < SIZE_AREA && coords.Y >= 0 && coords.Y < SIZE_AREA)
				{
					AddShip(0, coords.X, coords.Y);
				}			
			}
			else if (stady == GameStady::GAMEPROCESS)
			{
				coords.X = coords.X - 30;

				coords = CalcCoords(coords);
				
				if (coords.X < 0 || coords.X >= SIZE_AREA || coords.Y < 0 || coords.Y >= SIZE_AREA)
				{
					return 0;
				}

				if (CompArea[coords.Y][coords.X] == 1)
				{
					CompArea[coords.Y][coords.X] = 2;

					int ShipID = GetShipID(Players::COMPUTER, coords.X, coords.Y);

					if (ShipID != -1)
					{
						sGame.CompShips[ShipID].Killcount--;
					}

					if (CheckKillShip(sGame.CompShips[ShipID]))
					{
						SetShipKill(sGame.CompShips[ShipID], Players::COMPUTER);

						if (CheckAllKill(Players::COMPUTER))
						{
							sGame.thisGame = GameStady::GAMEEND;
						}
					}
				}
				else if (!CompArea[coords.Y][coords.X])
				{
					CompArea[coords.Y][coords.X] = 3;

					sGame.Walk = true;
				}
			}
		}
		else if (all_events[i].Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
		{
			if (stady == GameStady::ADDSHIPS)
			{
				coords = CalcCoords(coords);

				if (coords.X >= 0 && coords.X < SIZE_AREA && coords.Y >= 0 && coords.Y < SIZE_AREA)
				{
					AddShip(1, coords.X, coords.Y);
				}
			}
		}
		//------------------------------------------------------------
	}
	
	return FALSE;
}

COORD CalcCoords(COORD c)
{
	c.Y = c.Y / 2 - 1;
	c.X = c.X / 2 - 2;
	return c;
}