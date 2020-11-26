#include "checkers.h"

void StoreBoard(Board board, char* filename) // fun stores the board to file
{
	unsigned char arr[2];
	int i, j;

	FILE* storeboardfile = fopen(filename, "wb");
	Check_File_Allocation(storeboardfile);

	for (i = 0; i < BOARD_SIZE; i++) // run on rows
	{
		arr[0] = 0;
		arr[1] = 0;

		for (j = 0; j < BOARD_SIZE; j++) // runs on cols
		{
			if (board[i][j] == PLAYER1) // T '01' so val is 1
				Update_Arr(arr, j, 1);

			if (board[i][j] == PLAYER2) // B '10' so val is 2
				Update_Arr(arr, j, 2);

		}

		fwrite(arr, sizeof(arr), 1, storeboardfile); //write row to file
	}

	fclose(storeboardfile);
}

void Update_Arr(unsigned char arr[2], int rowindex, unsigned char currplayerval) // fun updates the arr
{
	int arrindex = 0; // first Cell for RowIndex 0-3
	char temp;

	if (rowindex > 3) // Seconed Cell for RowIndex 4-7
	{
		arrindex = 1; //Seconed Cell
		rowindex = rowindex - 4;
	}

	temp = currplayerval << (6 - (2 * rowindex)); // move val to correct spot
	arr[arrindex] = arr[arrindex] | temp;

}

void Check_File_Allocation(void* ptr) // Fun checks the allocation.
{
	if (ptr == NULL) // memory Allocation failed
	{
		printf("File allocation error\n");
		exit(FILE_ERROR_CODE);
	}
}