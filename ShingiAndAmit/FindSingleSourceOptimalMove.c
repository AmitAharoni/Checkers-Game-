#include "checkers.h"

SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree) // Fun creates optimal move list from tree
{
	SingleSourceMovesList* reslist;
	if (moves_tree == NULL) // for empty spot tree
		return NULL;
	else
	{
		reslist = Make_Empty_Single_List();
		FindSingleSourceOptimalMoveAux(reslist, moves_tree->source);
	}

	return reslist;
}

void FindSingleSourceOptimalMoveAux(SingleSourceMovesList* lst, SingleSourceMovesTreeNode* root) // Helper
{
	srand(time(NULL));
	int LeftHeiget = 0, RightHeiget = 0, random = rand() % 2;
	SingleSourceMovesListCell* cellToAdd = Create_New_List_Cell(root->pos, root->total_captures_so_far, NULL); // creates new cell

	if (root->next_move[0] == NULL && root->next_move[1] == NULL) // leaf
		Add_To_Single_List(lst, cellToAdd);
	else
	{
		if (root->next_move[0] != NULL) // L.SUBTREE
			Get_Level(root->next_move[0], 1, &LeftHeiget);

		if (root->next_move[1] != NULL)// R.SUBTREE
			Get_Level(root->next_move[1], 1, &RightHeiget);

		if (LeftHeiget > RightHeiget)
		{
			Add_To_Single_List(lst, cellToAdd);
			FindSingleSourceOptimalMoveAux(lst, root->next_move[0]); // REC LEFT
		}
		else if (LeftHeiget < RightHeiget)
		{
			Add_To_Single_List(lst, cellToAdd);
			FindSingleSourceOptimalMoveAux(lst, root->next_move[1]);// REC RIGHT
		}
		else // for equal case go random
		{
			Add_To_Single_List(lst, cellToAdd);
			FindSingleSourceOptimalMoveAux(lst, root->next_move[random]); // REC random left or right
		}
	}
}

void Add_To_Single_List(SingleSourceMovesList* lst, SingleSourceMovesListCell* curr) // add to list
{
	if (lst->head == NULL) // add to emptylist
	{
		lst->head = curr;
		lst->tail = curr;
	}
	else // addtotail
	{
		lst->tail->next = curr;
		lst->tail = curr;
	}
}

SingleSourceMovesListCell* Create_New_List_Cell(checkersPos* pos, unsigned short cap, SingleSourceMovesListCell* next)// Fun creates new cell.
{
	SingleSourceMovesListCell* curr = (SingleSourceMovesListCell*)malloc(sizeof(SingleSourceMovesListCell));
	Check_Memory_Allocation(curr);
	curr->position = (checkersPos*)malloc(sizeof(checkersPos));
	Check_Memory_Allocation(curr->position);

	curr->position->row = pos->row;
	curr->position->col = pos->col;
	curr->captures = cap;
	curr->next = next;

	return curr;
}

void Get_Level(SingleSourceMovesTreeNode* root, int currlevel, int* counter)// Get level of tree. leaf level is 1
{
	if (currlevel > *counter) // update counter
		*counter = currlevel;

	if (root->next_move[0] != NULL)
		Get_Level(root->next_move[0], currlevel + 1, counter); // REC LEFT
	if (root->next_move[1] != NULL)
		Get_Level(root->next_move[1], currlevel + 1, counter); // REC RIGHT
}