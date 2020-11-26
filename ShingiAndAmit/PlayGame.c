#include "checkers.h"

void PlayGame(Board board, Player starting_player) // fun runs the game
{
	checkersPos from, to;
	Board tempboard;
	int players_counter, is_game_finish = 0;

	Print_Board(board);
	players_counter = Count_Board_Pieces(board);
	Copy_Board(tempboard, board);
	Turn(board, starting_player);

	while (players_counter != 0 && is_game_finish != 1) // checks if the game hasnt come to an end
	{
		Update_Move(tempboard, board, &from, &to, starting_player);
		is_game_finish = Check_Win_Fun(board, &starting_player, from, to);
		printf("\n");
		if (is_game_finish != 1)
			players_counter = Count_Board_Pieces(board);
		if (players_counter != 0 && is_game_finish != 1)
		{
			Copy_Board(tempboard, board); //save the board and continue play
			Turn(board, starting_player);
		}
		Print_Board(board);

	}
}

void Print_Board(Board board) // Fun prints board 
{
	int i, j;
	char col = 'A';
	printf("+-+-+-+-+-+-+-+-+-+\n");
	printf("+ |1|2|3|4|5|6|7|8|\n");
	printf("+-+-+-+-+-+-+-+-+-+\n");
	for (i = 0; i < 8; i++)
	{
		printf("|%c", col++);
		for (j = 0; j < 8; j++)
		{
			if (board[i][j] == PLAYER1)
				printf("|T");
			else if (board[i][j] == PLAYER2)
				printf("|B");
			else
				printf("| ");
		}
		printf("|\n");
		printf("+-+-+-+-+-+-+-+-+-+\n");
	}
}

int Count_Board_Pieces(Board board) // fun counts how many pieces for both players, return lower
{
	int i, j, player1Counter = 0, player2Counter = 0;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (board[i][j] == PLAYER1)
				player1Counter++;
			else if (board[i][j] == PLAYER2)
				player2Counter++;
		}
	}
		return(Check_Board_Pieces(player1Counter, player2Counter, board));
}

int Check_Board_Pieces(int player1pieces, int player2pieces, Board board) // return the lower num of pieces
{
	if (player1pieces == 0)
		printf("player2 - B WINS!\n");
	else if (player2pieces == 0)
		printf("player1 - T WINS!\n");

	return min(player1pieces, player2pieces); // return min
}

void Copy_Board(Board resboard, Board boardtocopy) // Fun copy board from source to des
{
	int i, j;
	for (i = 0; i < BOARD_SIZE; i++) //run on rows
	{
		if (i % 2 == 0)
			j = 1;
		else
			j = 0;
		for (; j < BOARD_SIZE; j = j + 2) //run on cols
			resboard[i][j] = boardtocopy[i][j];
	}
}

int Check_Win_Fun(Board board, Player* starting_player, checkersPos from, checkersPos to) // fun indicates if someone win\tie
{
	int res = 0;
	if (board[0][0] == TIESIGN) // tie case
	{
		printf("\n   ITS A TIE!\n");
		res = 1;
		return res;
	}
	if (*starting_player == PLAYER1) // player1 turn
	{
		printf("player TOP_DOWN's turn\n");
		printf("%c%c->%c%c\n", from.row, from.col, to.row, to.col);
		*starting_player = PLAYER2; //change player
		if (to.row == 'H') //PLAYER1 wins
		{
			printf("\n   PLAYER1 - T WINS!\n");
			res = 1;
		}
	}
	else // player2 turn
	{
		printf("player BOTTOM_UP's turn\n");
		printf("%c%c->%c%c\n", from.row, from.col, to.row, to.col);
		*starting_player = PLAYER1; //change player
		if (to.row == 'A') //PLAYER2 wins
		{

			printf("\n   PLAYER2 - B WINS!\n");
			res = 1;
		}
	}
	return res;
}

void Update_Move(Board tempboard, Board board, checkersPos* from, checkersPos* to, Player currplayer) // updates from, to.
{
	int i, j;

	for (i = 0; i < BOARD_SIZE; i++) // run on rows
	{
		if (i % 2 == 0)
			j = 1;
		else
			j = 0;
		for (; j < BOARD_SIZE; j = j + 2) //run on cols
		{
			if (tempboard[i][j] == currplayer && board[i][j] != currplayer) // update from
			{
				from->row = i + 'A';
				from->col = j + '1';
				if (currplayer == PLAYER2)
					i = j = 8; // stop running 
			}

			if (board[i][j] == currplayer && tempboard[i][j] != currplayer) // update to
			{
				to->row = i + 'A';
				to->col = j + '1';
				if (currplayer == PLAYER1)
					i = j = 8; // stop running
			}
		}
	}
}
