#include "chengine.h"


int main()
{
	CHESSBOARD board[1];
	
	ParseFen(board, trickyPos);
	
	PrintPosition(board);
	PrintBoard(board);
	//PrintAttackBoard(board, black);
	
	MOVELIST movelist[1];
	movelist->moveCount = 0;
	
	int move = SetMove(e7, e8, wQ, 1, 0, 1);
	int move1 = SetMove(e2, e4, 0, 1, 1, 0);
	int move2 = SetMove(d2, d1, bN, 0, 0, 1);
	
	
	AddMove(movelist, move);
	AddMove(movelist, move1);
	AddMove(movelist, move2);

	
	PrintMoveList(movelist);
	
	
	return 0;
}
