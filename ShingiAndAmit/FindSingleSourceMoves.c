#include "checkers.h"

SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos* src)// Fun creates Source Move tree 
{
	SingleSourceMovesTree* res;
	char currplayer = board[src->row - 'A'][src->col - '1'];
	int player_direction = DOWN;  // assume player1
	int is_captured_0 = 0, is_captured_1 = 0;

	if (currplayer == NOPLAYER)
		return NULL;
	else
	{
		res = (SingleSourceMovesTree*)malloc(sizeof(SingleSourceMovesTree));
		Check_Memory_Allocation(res);
		res->source = Create_New_Tree_Node(board, src->row, src->col, 0);

		if (currplayer == PLAYER2)  // determine player direction
			player_direction = UP;

		FindSingleSourceMovesAux(board, res->source, currplayer, LEFT, player_direction,&is_captured_0);// REC LEFT
		FindSingleSourceMovesAux(board, res->source, currplayer, RIGHT, player_direction, &is_captured_1);// REC RIGHT
		Make_Best_Move(is_captured_0, is_captured_1, res);

			if(res->source->next_move[0] == NULL && res->source->next_move[1] == NULL)  
			{
				Free_Single_Tree(res);
				return NULL;
			}
	}
	return res;
}

void FindSingleSourceMovesAux(Board board, SingleSourceMovesTreeNode* root, char currPlayer, int changeCol, int changeRow, int* captureFlag)// Helper
{
	Board tempboard;
	SingleSourceMovesTreeNode* currNode;
	int next_move_index = 0, currRootCaptures = root->total_captures_so_far;
	char nextRow = root->pos->row + changeRow, nextCol = root->pos->col + changeCol, opponent = PLAYER2;
	char next_position = board[nextRow - 'A'][nextCol - '1'];

	if (changeCol == RIGHT) // determine next move index
		next_move_index = 1;
	if (currPlayer == PLAYER2)  // determine opponent sign
		opponent = PLAYER1;

	if (Check_Borders(nextRow, nextCol)) // next move borders are legal
	{
		if ((next_position == opponent))
		{
			if (Is_Capture(board, (nextRow + changeRow), (nextCol + changeCol))) // check capture
			{
				Copy_Board(tempboard, board);
				Update_Board_For_Tree(tempboard, root, nextRow, nextCol, (nextRow + changeRow), (nextCol + changeCol), currPlayer);
				currNode = Create_New_Tree_Node(tempboard, (nextRow + changeRow), (nextCol + changeCol), currRootCaptures + 1); // capture+1
				root->next_move[next_move_index] = currNode; // connects the tree Node
				FindSingleSourceMovesAux(board, currNode, currPlayer, LEFT, changeRow, captureFlag);// REC LEFT
				FindSingleSourceMovesAux(board, currNode, currPlayer, RIGHT, changeRow, captureFlag); // REC RIGHTs
				*captureFlag = 1;
			}
		}
		else if (next_position != PLAYER1 && next_position != PLAYER2 && currRootCaptures == 0) // NO captures at all.
		{
			Copy_Board(tempboard, board);
			Update_Board_For_Tree(tempboard, root,nextRow ,nextCol , (nextRow + changeRow), (nextCol + changeCol),  currPlayer);
			currNode = Create_New_Tree_Node(tempboard, nextRow, nextCol, root->total_captures_so_far);
			root->next_move[next_move_index] = currNode; // connects The tree Nodes
		}
	}
}

SingleSourceMovesTreeNode* Create_New_Tree_Node(Board board, char row, char col, unsigned short capture) // Fun creates new node.
{
	SingleSourceMovesTreeNode* res = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
	Check_Memory_Allocation(res);
	res->pos = (checkersPos*)malloc(sizeof(checkersPos));
	Check_Memory_Allocation(res->pos);

	Copy_Board(res->board, board);
	res->pos->row = row;
	res->pos->col = col;
	res->total_captures_so_far = capture;
	res->next_move[0] = NULL;
	res->next_move[1] = NULL;

	return res;
}

int Is_Capture(Board board, char rowToCheck, char colToCheck) // Fun checks if next move is Capture.
{
	char currPosition = board[rowToCheck - 'A'][colToCheck - '1'];
	if (Check_Borders(rowToCheck, colToCheck)) // next move borders are legal
	{
		if (currPosition != PLAYER1 && currPosition != PLAYER2) // next spot is empty so capture 
			return TRUE;
	}
	return FALSE;
}

int Check_Borders(char rowToCheck, char colToCheck)// Fun checks if next move is in borders.
{
	if (rowToCheck >= 'A' && rowToCheck <= 'H' && colToCheck >= '1' && colToCheck <= '8')
		return TRUE; // Move is legal

	return FALSE;
}

void Check_Memory_Allocation(void* ptr) // Fun checks the allocation.
{
	if (ptr == NULL) // memory Allocation failed
	{
		printf("Memory allocation error\n");
		exit(MALLOC_ERROR_CODE);
	}
}

SingleSourceMovesList* Make_Empty_Single_List() // fun makes empty list
{
	SingleSourceMovesList* lst = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
	Check_Memory_Allocation(lst);

	lst->head = lst->tail = NULL;

	return lst;
}

void Make_Best_Move(int cap0, int cap1, SingleSourceMovesTree* tree) // fun picks the best move in case of move\capture
{
	if (cap0 < cap1) // if any dircetion is with capture and the other without, put null in the other to insure capture
	{
		if (tree->source->next_move[0] != NULL) 
		{
			Free_Single_Tree_Aux(tree->source->next_move[0]);
			tree->source->next_move[0] = NULL;
		}
	}
	else if (cap0 > cap1)
	{
		if (tree->source->next_move[1] != NULL)
		{
			Free_Single_Tree_Aux(tree->source->next_move[1]);
			tree->source->next_move[1] = NULL;
		}
	}
}

void Update_Board_For_Tree(Board board, SingleSourceMovesTreeNode* curr, char row, char col,char rowAfterCap,char colAfterCap, Player player)// fun updated board for tree 
{
	if (board[row - 'A'][col - '1'] != PLAYER1 && board[row - 'A'][col - '1'] != PLAYER2)
	{
			board[curr->pos->row - 'A'][curr->pos->col - '1'] = NOPLAYER; // clear orignal spot
			board[row - 'A'][col - '1'] = player; // new spot
	}
	else
	{
		board[curr->pos->row - 'A'][curr->pos->col - '1'] = NOPLAYER; // clear orignal spot
		board[row - 'A'][col - '1'] = NOPLAYER;// clear eaten spot
		board[rowAfterCap - 'A'][colAfterCap - '1'] = player; // new spot
	}
}
