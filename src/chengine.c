#include "chengine.h"


int main()
{
	CHESSBOARD board[1];
	
	ParseFen(board, trickyPos);
	
	PrintPosition(board);
	PrintBoard(board);
	
	PrintAttackBoard(board, black);
	
	return 0;
}
