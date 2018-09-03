#include "chengine.h"


int main()
{
	CHESSBOARD board[1];
	ParseFen(board, trickyPos);
	
	PerftTest(board, 4);
	
	return 0;
}
