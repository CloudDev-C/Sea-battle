#include "Game.h"
#include "Graphics.h"
#include <algorithm>

GameData sGame;

int UserArea[SIZE_AREA][SIZE_AREA] = {};
int CompArea[SIZE_AREA][SIZE_AREA] = {};

BOOL CheckArea(Ship ship_t, Players player, int X, int Y, bool orient)
{
	if (!orient)
	{
		for (int i = Y - 1; i <= Y + 1; i++)
		{
			if (i < 0 || i >= 10) continue;

			for (int j = X - 1; j < X + ship_t.shipSize + 1; j++)
			{
				if (j < 0)
				{
					continue;
				}

				if (j >= 10)
				{
					if (X + ship_t.shipSize != 10)
					{
						return FALSE;
					}
					else
					{
						continue;
					}
				}

				if (player == Players::COMPUTER)
				{
					if (CompArea[i][j] != 0)
					{
						return FALSE;
					}
				}
				else
				{
					if (UserArea[i][j] != 0)
					{
						return FALSE;
					}
				}
			}
		}
	}
	else
	{
		for (int i = Y - 1; i < Y + ship_t.shipSize + 1; i++)
		{
			if (i < 0)
			{
				continue;
			}

			if (i >= 10)
			{
				if (Y + ship_t.shipSize != 10)
				{
					return FALSE;
				}
				else
				{
					continue;
				}
			}

			for (int j = X - 1; j <= X + 1; j++)
			{
				if (j < 0 || j >= 10)
				{
					continue;
				}

				if (player == Players::COMPUTER)
				{
					if (CompArea[i][j] != 0)
					{
						return FALSE;
					}
				}
				else
				{
					if (UserArea[i][j] != 0)
					{
						return FALSE;
					}
				}
			}
		}
	}

	return TRUE;
}

void SetNullArea()
{
	for (int i = 0; i < SIZE_AREA; i++)
	{
		for (int j = 0; j < SIZE_AREA; j++)
		{
			CompArea[i][j] = 0;
		}
	}
}

void AddShip(bool orientation, int X, int Y)
{
	if (CheckArea(sGame.UserShips[sGame.UserShipCount], Players::USER, X, Y, orientation))
	{
		if (!orientation)
		{
			for (int i = 0; i < sGame.UserShips[sGame.UserShipCount].shipSize; i++)
			{
				UserArea[Y][X] = 1;

				sGame.UserShips[sGame.UserShipCount].ship[i].Y = Y;
				sGame.UserShips[sGame.UserShipCount].ship[i].X = X;
				sGame.UserShips[sGame.UserShipCount].orient = orientation;
				X++;
			}
		}
		else
		{
			for (int i = 0; i < sGame.UserShips[sGame.UserShipCount].shipSize; i++)
			{
				UserArea[Y][X] = 1;

				sGame.UserShips[sGame.UserShipCount].ship[i].Y = Y;
				sGame.UserShips[sGame.UserShipCount].ship[i].X = X;
				sGame.UserShips[sGame.UserShipCount].orient = orientation;
				Y++;
			}
		}

		sGame.UserShipCount++;
	}

	if (sGame.UserShipCount == SHIPS_COUNT)
	{
		sGame.thisGame = GameStady::GAMEPROCESS;
		sGame.Walk = rand() % 2;
	}
}

void GameInit()
{
	sGame.UserShips = new Ship[10];
	sGame.CompShips = new Ship[10];
	sGame.UserShipCount = 0;
	sGame.thisGame = GameStady::ADDSHIPS;
	//====
	sGame.mode = 0;
	sGame.X = -1;
	sGame.Y = -1;

	sGame.dirs.push_back(3);
	sGame.dirs.push_back(2);
	sGame.dirs.push_back(1);
	sGame.dirs.push_back(0);

	for (int i = 0; i < SHIPS_COUNT; i++)
	{
		sGame.UserShips[i].shipSize = ShipsSize[i];
		sGame.UserShips[i].Killcount = ShipsSize[i];
		sGame.UserShips[i].ship = new COORD[ShipsSize[i]];

		sGame.CompShips[i].shipSize = ShipsSize[i];
		sGame.CompShips[i].Killcount = ShipsSize[i];
		sGame.CompShips[i].ship = new COORD[ShipsSize[i]];
	}

	int ship_count = 0;
	int check_count = 0;

	while (ship_count < SHIPS_COUNT)
	{
		int X = rand() % 10;
		int Y = rand() % 10;
		int orientation = rand() % 2;

		if (CheckArea(sGame.CompShips[ship_count], Players::COMPUTER, X, Y, orientation))
		{
			if (!orientation)
			{
				for (int i = 0; i < sGame.CompShips[ship_count].shipSize; i++)
				{
					CompArea[Y][X] = 1;

					sGame.CompShips[ship_count].ship[i].Y = Y;
					sGame.CompShips[ship_count].ship[i].X = X;
					sGame.CompShips[ship_count].orient = orientation;
					X++;
				}
			}
			else
			{
				for (int i = 0; i < sGame.CompShips[ship_count].shipSize; i++)
				{
					CompArea[Y][X] = 1;

					sGame.CompShips[ship_count].ship[i].Y = Y;
					sGame.CompShips[ship_count].ship[i].X = X;
					sGame.CompShips[ship_count].orient = orientation;
					Y++;
				}
			}

			ship_count++;
		}

		check_count++;

		if (check_count >= 1000)
		{
			SetNullArea();
			check_count = 0;
			ship_count = 0;
		}
	}

}

void GameFreeMemory()
{
	for (int i = 0; i < SHIPS_COUNT; i++)
	{
		delete[] sGame.UserShips[i].ship;
		delete[] sGame.CompShips[i].ship;
	}
}

int GetShipID(Players player, int X, int Y)
{
	for (int i = 0; i < SHIPS_COUNT; i++)
	{
		if (player == Players::USER)
		{
			for (int j = 0; j < sGame.UserShips[i].shipSize; j++)
			{
				if (sGame.UserShips[i].ship[j].X == X && sGame.UserShips[i].ship[j].Y == Y)
				{
					return i;
				}
			}
		}
		else
		{
			for (int j = 0; j < sGame.CompShips[i].shipSize; j++)
			{
				if (sGame.CompShips[i].ship[j].X == X && sGame.CompShips[i].ship[j].Y == Y)
				{
					return i;
				}
			}
		}
	}

	return -1;
}

bool CheckKillShip(Ship ship_)
{
	if (ship_.Killcount <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void SetShipKill(Ship ship_, Players player)
{
	int X = ship_.ship[0].X;
	int Y = ship_.ship[0].Y;

	if (!ship_.orient)
	{
		for (int i = Y - 1; i <= Y + 1; i++)
		{
			if (i < 0 || i >= 10) continue;

			for (int j = X - 1; j < X + ship_.shipSize + 1; j++)
			{
				if (j < 0 || j >= 10)
				{
					continue;
				}

				if (player == Players::USER)
				{
					if (UserArea[i][j] != 2)
					{
						UserArea[i][j] = 3;
					}
				}
				else
				{
					if (CompArea[i][j] != 2)
					{
						CompArea[i][j] = 3;
					}
				}
			}
		}
	}
	else
	{
		for (int i = Y - 1; i < Y + ship_.shipSize + 1; i++)
		{
			if (i < 0 || i >= 10)
			{
				continue;
			}

			for (int j = X - 1; j <= X + 1; j++)
			{
				if (j < 0 || j >= 10)
				{
					continue;
				}

				if (player == Players::USER)
				{
					if (UserArea[i][j] != 2)
					{
						UserArea[i][j] = 3;
					}
				}
				else
				{
					if (CompArea[i][j] != 2)
					{
						CompArea[i][j] = 3;
					}
				}
			}
		}
	}
}


void ComputerStep()
{
	while (true)
	{
		if (sGame.mode == 0)
		{
			if (sGame.X == -1 && sGame.Y == -1)
			{
				sGame.X = rand() % SIZE_AREA;
				sGame.Y = rand() % SIZE_AREA;
			}

			if (UserArea[sGame.Y][sGame.X] == 1)
			{
				sGame.mode = 1;

				UserArea[sGame.Y][sGame.X] = 2;

				int ShipID = GetShipID(Players::USER, sGame.X, sGame.Y);

				if (ShipID != -1)
				{
					sGame.UserShips[ShipID].Killcount--;
				}

				if (CheckKillShip(sGame.UserShips[ShipID]))
				{
					SetShipKill(sGame.UserShips[ShipID], Players::USER);

					if (CheckAllKill(Players::USER))
					{
						sGame.thisGame = GameStady::GAMEEND;

						break;
					}

					UserArea[sGame.Y][sGame.X] = 2;

					sGame.X = -1;
					sGame.Y = -1;
					sGame.mode = 0;
					sGame.UserShips[ShipID].Killcount = 0;

					sGame.dirs.clear();

					sGame.dirs.push_back(3);
					sGame.dirs.push_back(2);
					sGame.dirs.push_back(1);
					sGame.dirs.push_back(0);
				}

				sGame.firstHitX = sGame.X;
				sGame.firstHitY = sGame.Y;

				if (!sGame.dirs.empty())
				{
					sGame.dir = sGame.dirs[sGame.dirs.size() - 1];
					sGame.dirs.pop_back();
				}
				else
				{
					sGame.dirs.push_back(3);
					sGame.dirs.push_back(2);
					sGame.dirs.push_back(1);
					sGame.dirs.push_back(0);
				}
			}
			else if (UserArea[sGame.Y][sGame.X] == 2 || UserArea[sGame.Y][sGame.X] == 3)
			{
				sGame.X = -1;
				sGame.Y = -1;
				continue;
			}
			else
			{
				sGame.Walk = false;
				UserArea[sGame.Y][sGame.X] = 3;
				sGame.X = -1;
				sGame.Y = -1;
				break;
			}
		}
		else if (sGame.mode == 1)
		{
			bool changeDir = 0;

			if (!sGame.dir)
			{
				if (sGame.X > 0)
				{
					sGame.X--;
				}
				else
				{
					changeDir = 1;
				}
			}
			else if (sGame.dir == 1)
			{
				if (sGame.X < SIZE_AREA - 1)
				{
					sGame.X++;
				}
				else
				{
					changeDir = 1;
				}
			}
			else if (sGame.dir == 2)
			{
				if (sGame.Y > 0)
				{
					sGame.Y--;
				}
				else
				{
					changeDir = 1;
				}

			}
			else if (sGame.dir == 3)
			{
				if (sGame.Y < SIZE_AREA - 1)
				{
					sGame.Y++;
				}
				else
				{
					changeDir = 1;
				}
			}

			if (changeDir)
			{
				if (!sGame.dirs.empty())
				{
					sGame.dir = sGame.dirs[sGame.dirs.size() - 1];
					sGame.dirs.pop_back();
				}
				else
				{
					sGame.dirs.push_back(3);
					sGame.dirs.push_back(2);
					sGame.dirs.push_back(1);
					sGame.dirs.push_back(0);
				}

				sGame.X = sGame.firstHitX;
				sGame.Y = sGame.firstHitY;

				continue;
			}

			int ShipID = GetShipID(Players::USER, sGame.X, sGame.Y);

			if (UserArea[sGame.Y][sGame.X] == 1 && sGame.UserShips[ShipID].Killcount > 1)
			{
				UserArea[sGame.Y][sGame.X] = 2;

				if (ShipID != -1)
				{
					sGame.UserShips[ShipID].Killcount--;
				}
			}
			else if (UserArea[sGame.Y][sGame.X] == 1 && sGame.UserShips[ShipID].Killcount == 1)
			{
				UserArea[sGame.Y][sGame.X] = 2;

				sGame.X = -1;
				sGame.Y = -1;
				sGame.mode = 0;
				sGame.UserShips[ShipID].Killcount = 0;

				sGame.dirs.clear();
				sGame.dirs.push_back(3);
				sGame.dirs.push_back(2);
				sGame.dirs.push_back(1);
				sGame.dirs.push_back(0);

				SetShipKill(sGame.UserShips[ShipID], Players::USER);

				if (CheckAllKill(Players::USER))
				{
					sGame.thisGame = GameStady::GAMEEND;

					break;
				}
			}
			else if (UserArea[sGame.Y][sGame.X] == 2 || UserArea[sGame.Y][sGame.X] == 3)
			{
				if (!sGame.dirs.empty())
				{
					sGame.dir = sGame.dirs[sGame.dirs.size() - 1];
					sGame.dirs.pop_back();
				}
				else
				{
					sGame.dirs.push_back(3);
					sGame.dirs.push_back(2);
					sGame.dirs.push_back(1);
					sGame.dirs.push_back(0);
				}

				sGame.X = sGame.firstHitX;
				sGame.Y = sGame.firstHitY;

				continue;
			}
			else
			{
				UserArea[sGame.Y][sGame.X] = 3;

				if (!sGame.dirs.empty())
				{
					sGame.dir = sGame.dirs[sGame.dirs.size() - 1];
					sGame.dirs.pop_back();
				}

				sGame.X = sGame.firstHitX;
				sGame.Y = sGame.firstHitY;
				sGame.Walk = false;

				break;
			}
		}
	}
}

bool CheckAllKill(Players player)
{
	if (player == Players::COMPUTER)
	{
		for (int i = 0; i < SHIPS_COUNT; i++)
		{
			if (sGame.CompShips[i].Killcount)
			{
				return false;
			}
		}
	}
	else
	{
		for (int i = 0; i < SHIPS_COUNT; i++)
		{
			if (sGame.UserShips[i].Killcount)
			{
				return false;
			}
		}
	}

	return true;
}
