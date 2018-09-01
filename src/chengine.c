#include "chengine.h"


int main()
{
	CHESSBOARD board[1];
	
	ParseFen(board, trickyPos);
	
	PrintPosition(board);
	PrintBoard(board);
	//PrintAttackBoard(board, black);
	
	MOVE move[1];
	move->move = 0;
	
	SetMove(move, e7, e8, wQ, 1, 1, 1);
	
	PrintMoveBinary(move);
	PrintMove(move);
	
	
	return 0;
}
