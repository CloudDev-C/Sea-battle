#include "Graphics.h"

char Letters[SIZE_AREA] = { 'A','B','C','D','E','F','G','H','I','J' };

void DrawShips(Players player, COORD coord)
{
	COORD ShipCoord = { 0,0 };

	ShipCoord.X = coord.X + 3;
	ShipCoord.Y = coord.Y + 2;

	if (player == Players::COMPUTER)
	{
		for (int i = 0; i < SIZE_AREA; i++)
		{
			for (int j = 0; j < SIZE_AREA; j++)
			{
				ShipCoord.X = coord.X + j * 2 + 3;
				ShipCoord.Y = coord.Y + i * 2 + 2;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ShipCoord);

				if (CompArea[i][j] == 2)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x04);
					std::cout << char(219);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
				}
				else if (CompArea[i][j] == 3)
				{
					std::cout << char(250);
				}

			}

			std::cout << std::endl;
		}
	}
	else
	{
		for (int i = 0; i < SIZE_AREA; i++)
		{
			for (int j = 0; j < SIZE_AREA; j++)
			{
				ShipCoord.X = coord.X + j * 2 + 3;
				ShipCoord.Y = coord.Y + i * 2 + 2;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ShipCoord);

				if (UserArea[i][j] == 1)
				{
					std::cout << char(219);
				}
				else if (UserArea[i][j] == 2)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x04);
					std::cout << char(219);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
				}
				else if (UserArea[i][j] == 3)
				{
					std::cout << char(250);
				}
			}
			std::cout << std::endl;
		}
	}
}

void DrawOneArea(HANDLE hConsole, COORD coord, Players player)
{
	COORD dCoord = { 0, 0 };
	COORD ShipCoord = { 0,0 };

	dCoord.X = coord.X + 3;

	for (int i = 0; i < SIZE_AREA; i++)
	{
		SetConsoleCursorPosition(hConsole, dCoord);

		std::cout << Letters[i];

		dCoord.X += 2;
	}

	dCoord.X = coord.X;
	dCoord.Y = coord.Y + 2;

	for (int i = 0; i < SIZE_AREA; i++)
	{
		SetConsoleCursorPosition(hConsole, dCoord);

		std::cout << i + 1;

		dCoord.Y += 2;
	}

	dCoord.X = coord.X + 2;
	dCoord.Y = coord.Y + 1;

	for (int i = 0; i <= SIZE_AREA * 2; i++)
	{
		for (int j = 0; j <= SIZE_AREA * 2; j++)
		{
			SetConsoleCursorPosition(hConsole, dCoord);

			if (i == 0 && j == 0)
			{
				std::cout << char(201);
			}
			else if (i == 0 && j == SIZE_AREA * 2)
			{
				std::cout << char(187);
			}
			else if (i == SIZE_AREA * 2 && j == SIZE_AREA * 2)
			{
				std::cout << char(188);
			}
			else if (i == SIZE_AREA * 2 && j == 0)
			{
				std::cout << char(200);
			}
			else if (!(j % 2) && i == 0)
			{
				std::cout << char(203);
			}
			else if (j == 0 && !(i % 2))
			{
				std::cout << char(204);
			}
			else if (i == SIZE_AREA * 2 && !(j % 2))
			{
				std::cout << char(202);
			}
			else if (j == SIZE_AREA * 2 && !(i % 2))
			{
				std::cout << char(185);
			}
			else if (!(i % 2) && (j % 2))
			{
				std::cout << char(205);
			}
			else if (!(j % 2) && (i % 2))
			{
				std::cout << char(186);
			}
			else if (!(j % 2) && !(i % 2))
			{
				std::cout << char(206);
			}

			dCoord.X++;
		}

		dCoord.Y++;
		dCoord.X = coord.X + 2;
	}	
}

void DrawInfo(HANDLE hConsole)
{

	COORD coord = { 0, 22 };
	SetConsoleCursorPosition(hConsole, coord);

	std::cout << "                                                                                            \n";
	std::cout << "                                                                                            \n";
	std::cout << "                                                                                            \n";
	std::cout << "                                                                                            \n";
	std::cout << "                                                                                            \n";
	std::cout << "                                                                                            \n";

	if (sGame.thisGame == GameStady::ADDSHIPS)
	{
		SetConsoleCursorPosition(hConsole, coord);

		std::cout << "Click the left mouse button on the field to deliver the ship horizontally\n";
		std::cout << "Click the right mouse button on the field to deliver the ship vertically\n";
	}
	else if (sGame.thisGame == GameStady::GAMEPROCESS)
	{
		SetConsoleCursorPosition(hConsole, coord);

		if (!sGame.Walk)
		{
			std::cout << "Your move.\n";
		}
		else
		{
			std::cout << "Computer Move.\n";
		}
	}
}

void Draw(HANDLE hConsole)
{
	COORD coord = { 1, 0 };

	DrawOneArea(hConsole, coord, Players::USER);

	DrawShips(Players::USER, coord);

	coord = { 31, 0 };

	DrawOneArea(hConsole, coord, Players::COMPUTER);

	DrawShips(Players::COMPUTER, coord);
}