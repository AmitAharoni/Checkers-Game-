#include "checkers.h"

void Turn(Board board, Player player) // fun runs specific turn for player
{
	int playerDirection = DOWN, playerside = LEFT; // assume player1, going left
	MultipleSourceMovesList* lst = FindAllPossiblePlayerMoves(board, player);
	SingleSourceMovesListCell* curr, *nextMove;
	if (lst->head == NULL) // tie case, multiple list is empty, end function
	{
		board[0][0] = TIESIGN;
		free(lst); //( multiplelist is empty )
		return;
	}
	curr = lst->tail->single_source_moves_list->head;
	nextMove = curr->next; 
	if (player == PLAYER2)  // determine player direction
	{
		playerDirection = UP;
		playerside = RIGHT;
	}
	if (curr->captures == 0 && nextMove == NULL) // move without captures
	{
		board[curr->position->row - 'A'][curr->position->col - '1'] = NOPLAYER; // clear orignal spot
		board[curr->position->row - 'A' + playerDirection][curr->position->col - '1' + playerside] = player; // new spot
	}
	else // capture
	{
		while (nextMove != NULL) // run on all list nodes
		{
			Update_Board_Capture(board, nextMove, curr, playerside, playerDirection, player); // updates board
			curr = nextMove; // advance
			nextMove = nextMove->next; // advance
		}
	}
	Free_Multpi(lst);
}

void Update_Board_Capture(Board board,SingleSourceMovesListCell* nextMove, SingleSourceMovesListCell* currMove, int playerside, int playerDirection, char player)// fun updates board for capture case
{
		if (nextMove->position->col > currMove->position->col) // go right
			playerside = RIGHT;
		else
			playerside = LEFT;

		board[currMove->position->row - 'A'][currMove->position->col - '1'] = NOPLAYER; // clear orignal spot
		board[currMove->position->row - 'A' + playerDirection][currMove->position->col - '1' + playerside] = NOPLAYER; // clear captured spot
		board[nextMove->position->row - 'A'][nextMove->position->col - '1'] = player; // new spot
}


void Free_Multpi(MultipleSourceMovesList* lst) // free multi list
{
	MultipleSourceMovesListCell* curr = lst->head, *next, *prev = NULL;
	while (curr != NULL)
	{
		Free_Single_List(curr->single_source_moves_list);
		next = curr->next;
		free(curr);
		curr = next;
	}
	free(lst);

}

void Free_Single_List(SingleSourceMovesList* lst) // free list
{
	SingleSourceMovesListCell* curr = lst->head, *next;
	while (curr != NULL)
	{
		free(curr->position);
		next = curr->next;
		free(curr);
		curr = next;
	}
	free(lst);
}