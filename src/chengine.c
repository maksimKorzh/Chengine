#include "chengine.h"


int main()
{
	CHESSBOARD board[1];
	
	ParseFen(board, trickyPos);
	
	PrintPosition(board);
	PrintBoard(board);
	PrintAttackBoard(board, black);
	
	unsigned int a = 0xf0ffffff;
	
	PrintMoveBinary(8);
	
	
	
	return 0;
}
