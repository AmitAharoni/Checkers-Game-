#include "checkers.h"

void LoadBoard(char* filename, Board board) // fun loads the board from file
{
	Player currplayersign;
	unsigned char arr[2];
	int i, j;

	FILE* storeboardfile = fopen(filename, "rb");
	Check_File_Allocation(storeboardfile);

	for (i = 0; i < BOARD_SIZE; i++)// runs on rows
	{
		fread(arr, sizeof(arr), 1, storeboardfile); //read row from file

		for (j = 0; j < BOARD_SIZE; j++) // runs on cols
		{
			currplayersign = Get_Sign(arr, j);
			board[i][j] = currplayersign; // T FOR PLAYER1, B FOR PLAYER2 ' ' (space) for NOPLAYER
		}
	}

	fclose(storeboardfile);
}

Player Get_Sign(unsigned char arr[2], int j) // T FOR PLAYER1, B FOR PLAYER2 ' ' (space) for NOPLAYER
{
	unsigned char LSB = 1;
	int arrindex = 0; // first Cell for j 0-3

	if (j > 3) // Seconed Cell for j 4-7
	{
		arrindex = 1; //Seconed Cell
		j = j - 4;
	}

	if (LSB << (6 - 2 * j) & arr[arrindex])
		return PLAYER1;

	if (LSB << (7 - 2 * j) & arr[arrindex])
		return PLAYER2;

	return NOPLAYER;
}