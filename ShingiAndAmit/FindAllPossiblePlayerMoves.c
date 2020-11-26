#include "checkers.h"


MultipleSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player player) // Fun creates optimal move list for player
{
	SingleSourceMovesTree* SingleTree;
	SingleSourceMovesList* SingleList;
	MultipleSourceMovesList* MultipleList = Make_Empty_Multiple_List();
	checkersPos currPos;
	int i, j = 0;

	for (i = 0; i < BOARD_SIZE; i++) // run on rows
	{
		if (i % 2 == 0)
			j = 1;
		else
			j = 0;
		for (; j < BOARD_SIZE; j = j + 2) //run on cols
		{
			if (board[i][j] == player)
			{
				currPos.row = (i + 'A');
				currPos.col = (j + '1');
				SingleTree = FindSingleSourceMoves(board, &currPos); //creates pawn tree
				SingleList = FindSingleSourceOptimalMove(SingleTree); //creates pawn optimal move list
				if (SingleTree != NULL) // if tree empty so single list empty as well
				{
					if (SingleTree->source->next_move[0] != NULL || SingleTree->source->next_move[1] != NULL)
						Add_To_Multiple_List(MultipleList, SingleList, player);

					Free_Single_Tree(SingleTree);
				}
			}
		}
	}
	return MultipleList;
}

void Free_Single_Tree(SingleSourceMovesTree* SingleTree) // free tree
{
	if (SingleTree->source != NULL)
	{
		Free_Single_Tree_Aux(SingleTree->source);
		free(SingleTree);
	}
}

void Free_Single_Tree_Aux(SingleSourceMovesTreeNode* root)// Helper
{
	if (root->next_move[0] != NULL)
		Free_Single_Tree_Aux(root->next_move[0]);

	if (root->next_move[1] != NULL)
		Free_Single_Tree_Aux(root->next_move[1]);

	free(root->pos);
	free(root);
}


void Add_To_Multiple_List(MultipleSourceMovesList* MultipleList, SingleSourceMovesList* SingleList, Player player )// add to list
{
	MultipleSourceMovesListCell* curr = Create_New_Multiple_Node(SingleList, NULL);
	MultipleSourceMovesListCell* prev;

	if (MultipleList->head == NULL)
		Add_To_Empty_Multiple_List(MultipleList, curr);
	else
	{
		prev = Find_Place_To_Multiple_Insert(MultipleList, SingleList->tail->captures, player);
		if (prev == NULL)
			Add_To_Head_Multiple(MultipleList, curr);
		else if (prev == MultipleList->tail)
			Add_To_Tail_Multiple(MultipleList, curr);
		else
			Add_To_Inner_Multiple(prev, curr);
	}
}


MultipleSourceMovesListCell* Create_New_Multiple_Node(SingleSourceMovesList* SingleList, MultipleSourceMovesListCell* next) // create new node
{
	MultipleSourceMovesListCell* curr = (MultipleSourceMovesListCell*)malloc(sizeof(MultipleSourceMovesListCell));
	Check_Memory_Allocation(curr);
	curr->single_source_moves_list = SingleList;
	curr->next = next;

	return curr;
}

MultipleSourceMovesListCell* Find_Place_To_Multiple_Insert(MultipleSourceMovesList* lst, unsigned short data, Player player)// find place to insert
{
	MultipleSourceMovesListCell* curr = lst->head;
	MultipleSourceMovesListCell* prev = NULL;
	if (player == PLAYER1)
	{
		while (curr != NULL && curr->single_source_moves_list->tail->captures <= data)
		{
			prev = curr;
			curr = curr->next;
		}
	}
	else // player2
	{
		while (curr != NULL && curr->single_source_moves_list->tail->captures < data)
		{
			prev = curr;
			curr = curr->next;
		}
	}

	return prev;
}


MultipleSourceMovesList* Make_Empty_Multiple_List() // make empty list
{
	MultipleSourceMovesList* lst = (MultipleSourceMovesList*)malloc(sizeof(MultipleSourceMovesList));
	Check_Memory_Allocation(lst);

	lst->head = lst->tail = NULL;

	return lst;
}

void Add_To_Empty_Multiple_List(MultipleSourceMovesList* lst, MultipleSourceMovesListCell* curr)// add to empty list
{
	lst->head = curr;
	lst->tail = curr;
}

void Add_To_Head_Multiple(MultipleSourceMovesList* lst, MultipleSourceMovesListCell* curr) // add to head
{
	curr->next = lst->head;
	lst->head = curr;
}

void Add_To_Tail_Multiple(MultipleSourceMovesList* lst, MultipleSourceMovesListCell* curr) // add to tail
{
	lst->tail->next = curr;
	lst->tail = curr;
}

void Add_To_Inner_Multiple(MultipleSourceMovesListCell* prev, MultipleSourceMovesListCell* curr) // add to innerplace
{
	curr->next = prev->next;
	prev->next = curr;
}