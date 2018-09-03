#include "chengine.h"


int main()
{
	CHESSBOARD board[1];
	
	ParseFen(board, trickyPos);
	
	PrintPosition(board);
	PrintBoard(board);
	//PrintAttackBoard(board, white);
	
	MOVELIST list[1];
	list->moveCount = 0;
	
	GenerateMoves(board, list);
	
	
	PrintMoveList(list);
	
	
	return 0;
}
