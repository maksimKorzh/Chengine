#include "chengine.h"


int main()
{
	CHESSBOARD board[1];
	
	ParseFen(board, "8/8/8/3n4/8/2k1K3/8/8 b - - 0 1 ");
	
	PrintPosition(board);
	PrintBoard(board);
	//PrintAttackBoard(board, white);
	
	MOVELIST list[1];
	list->moveCount = 0;
	
	GenerateMoves(board, list);
	
	
	PrintMoveList(list);
	
	
	return 0;
}
