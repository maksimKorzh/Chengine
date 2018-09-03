#include "chengine.h"


int main()
{
	CHESSBOARD board[1];
	
	ParseFen(board, initPos);
	
	//MOVELIST list[1];
	
	//PrintBoard(board);
	PerftTest(board, 3);
	
	
	
	return 0;
}
