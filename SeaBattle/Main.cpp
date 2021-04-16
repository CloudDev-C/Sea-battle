#include <iostream>
#include <Windows.h>
#include "Graphics.h"
#include <time.h>
#include "Game.h"
#include "Control.h"

int main()
{
	SetConsoleTitle("SeaBattle - V0.1");

	srand(time(NULL));
	rand();

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(hConsole, &info);
	info.bVisible = FALSE;
	SetConsoleCursorInfo(hConsole, &info);

	GameInit();

	while (true)
	{
		if (sGame.thisGame == GameStady::ADDSHIPS || !sGame.Walk)
		{
			Control(sGame.thisGame);
		}

		Draw(hConsole);

		DrawInfo(hConsole);

		if (sGame.thisGame == GameStady::GAMEPROCESS)
		{
			if (sGame.Walk)
			{
				Sleep(1000);

				ComputerStep();
			}
		}
		else if (sGame.thisGame == GameStady::GAMEEND)
		{
			break;
		}
	}

	system("cls");

	if (!sGame.Walk)
	{
		std::cout << "You Win!" << std::endl;
	}
	else
	{
		std::cout << "Computer Win!" << std::endl;;
	}

	GameFreeMemory();

	system("PAUSE");

	return 0;
}