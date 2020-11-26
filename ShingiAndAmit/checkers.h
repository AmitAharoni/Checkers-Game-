#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// DEFINE
#define BOARD_SIZE 8
#define PLAYER1 'T'
#define PLAYER2 'B'
#define NOPLAYER ' '
#define TIESIGN '$'
#define LEFT (-1)
#define RIGHT 1
#define UP (-1)
#define DOWN 1
#define TRUE 1
#define FALSE 0
#define MALLOC_ERROR_CODE (5)
#define FILE_ERROR_CODE (6)

// TYPEDEF
typedef char Board[BOARD_SIZE][BOARD_SIZE];

typedef char Player;

typedef struct _checkersPos
{
	char row, col;
} checkersPos;

typedef struct _SingleSourceMovesTreeNode
{
	Board board;
	checkersPos* pos;
	unsigned short total_captures_so_far; // מספר הדילוגים עד כה
	struct _SingleSourceMovesTreeNode* next_move[2]; // יעדי התנועה
} SingleSourceMovesTreeNode;

typedef struct _SingleSourcesMovesTree
{
	SingleSourceMovesTreeNode* source;
} SingleSourceMovesTree;

typedef struct _SingleSourceMovesListCell
{
	checkersPos* position;
	unsigned short captures;
	struct _SingleSourceMovesListCell* next;

} SingleSourceMovesListCell;

typedef struct _SingleSourceMovesList
{
	SingleSourceMovesListCell* head;
	SingleSourceMovesListCell* tail;
} SingleSourceMovesList;

typedef struct _multipleSourceMovesListCell
{
	SingleSourceMovesList* single_source_moves_list;
	struct _multipleSourceMovesListCell* next;
} MultipleSourceMovesListCell;

typedef struct _multipleSourceMovesList
{
	MultipleSourceMovesListCell* head;
	MultipleSourceMovesListCell* tail;
} MultipleSourceMovesList;

// FUNCTIONS

SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos* src); // Fun creates Source Move tree 
void FindSingleSourceMovesAux(Board board, SingleSourceMovesTreeNode* root, char currplayer, int changecol, int changerow, int* flag);// Helper
SingleSourceMovesTreeNode* Create_New_Tree_Node(Board board, char row, char col, unsigned short capture); // Fun creates new node.
int Is_Capture(Board board, char rowtocheck, char coltocheck); // Fun checks if next move is Capture.
int Check_Borders(char rowtocheck, char coltocheck); // Fun checks if next move is in borders.
void Check_Memory_Allocation(void* ptr); // Fun checks the allocation.
SingleSourceMovesList* Make_Empty_Single_List(); // fun makes empty list
void Make_Best_Move(int cap0, int cap1, SingleSourceMovesTree* tree); // fun picks the best move in case of move\capture
void Update_Board_For_Tree(Board board, SingleSourceMovesTreeNode* curr, char row, char col, char rowAfterCap, char colAfterCap, Player player); // fun updated board for tree 


SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree); // Fun creates optimal move list from tree
void FindSingleSourceOptimalMoveAux(SingleSourceMovesList* lst, SingleSourceMovesTreeNode* root); // Helper
void Add_To_Single_List(SingleSourceMovesList* lst, SingleSourceMovesListCell* curr);// add to list
SingleSourceMovesListCell* Create_New_List_Cell(checkersPos* pos, unsigned short cap, SingleSourceMovesListCell* next);// Fun creates new cell.
void Get_Level(SingleSourceMovesTreeNode* root, int currlevel, int* counter); // Get level of tree. leaf level is 1


MultipleSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player player); // Fun creates optimal move list for player
void Free_Single_Tree(SingleSourceMovesTree* singletree); // free tree
void Free_Single_Tree_Aux(SingleSourceMovesTreeNode* root); // Helper
void Add_To_Multiple_List(MultipleSourceMovesList* multiplelist, SingleSourceMovesList* singlelist, Player player);// add to list
MultipleSourceMovesListCell* Create_New_Multiple_Node(SingleSourceMovesList* singleList, MultipleSourceMovesListCell* next); // create new node
MultipleSourceMovesListCell* Find_Place_To_Multiple_Insert(MultipleSourceMovesList* lst, unsigned short data, Player player); // find place to insert
MultipleSourceMovesList* Make_Empty_Multiple_List(); // make empty list
void Add_To_Empty_Multiple_List(MultipleSourceMovesList* lst, MultipleSourceMovesListCell* curr); // add to empty list
void Add_To_Head_Multiple(MultipleSourceMovesList* lst, MultipleSourceMovesListCell* curr); // add to head
void Add_To_Tail_Multiple(MultipleSourceMovesList* lst, MultipleSourceMovesListCell* curr); // add to tail
void Add_To_Inner_Multiple(MultipleSourceMovesListCell* prev, MultipleSourceMovesListCell* curr); // add to innerplace


void Turn(Board board, Player player);// fun runs specific turn for player
void Update_Board_Capture(Board board, SingleSourceMovesListCell* nextmove, SingleSourceMovesListCell* currmove, int playerside, int playerdirection, char player);// fun updates board for capture case
void Free_Multpi(MultipleSourceMovesList* lst);// free multi list
void Free_Single_List(SingleSourceMovesList* lst); // free list


void StoreBoard(Board board, char* filename); // fun stores the board to file
void Update_Arr(unsigned char arr[2], int rowindex, unsigned char currplayerval); // fun updates the arr
void Check_File_Allocation(void* ptr); // Fun checks the allocation.


void LoadBoard(char* filename, Board board); // fun loads the board from file
Player Get_Sign(unsigned char arr[2], int j); // T FOR PLAYER1, B FOR PLAYER2 ' ' (space) for NOPLAYER

void PlayGame(Board board, Player starting_player); // Fun runs the GAME!
void Print_Board(Board board); // Fun prints board 
int Count_Board_Pieces(Board board); // fun counts how many pieces for both players, return lower
int Check_Board_Pieces(int player1pieces, int player2pieces, Board board); // return the lower num of pieces
void Copy_Board(Board ResBoard, Board BoardToCopy); // Fun copy board from source to des
int Check_Win_Fun(Board board, Player* starting_player, checkersPos from, checkersPos to); // fun indicates if someone win\tie
void Update_Move(Board tempboard, Board board, checkersPos* from, checkersPos* to, Player currplayer); // updates from, to.

