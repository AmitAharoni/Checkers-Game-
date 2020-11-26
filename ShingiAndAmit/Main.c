#include "checkers.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

void main()
{
	Board board;
	int i, j;

	for (i = 0; i < 3; i++) // PLAYER1
	{
		for (j = 0; j < 8; j++)
		{
			if (i % 2 == 0)
			{
				if (j % 2 != 0)
					board[i][j] = PLAYER1;
			}
			else
			{
				if (j % 2 == 0)
					board[i][j] = PLAYER1;
			}
		}
	}

	for (i = 5; i < 8; i++) // PLAYER2
	{
		for (j = 0; j < 8; j++)
		{
			if (i % 2 == 0)
			{
				if (j % 2 != 0)
					board[i][j] = PLAYER2;
			}
			else
			{
				if (j % 2 == 0)
					board[i][j] = PLAYER2;
			}
		}
	}


	PlayGame(board, PLAYER1); // player1 starts the game

	if (_CrtDumpMemoryLeaks())
	{
		printf("memory leak detected!");
	}
	
	system("pause");
}