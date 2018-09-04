#include "chengine.h"


int main()
{
	CHESSBOARD board[1];
	ParseFen(board, trickyPos);
	PrintBoard(board);
	
	MOVE bestMove[1];
	bestMove[0] = SearchPosition(board, 3);
	
	PrintMove(bestMove->move);
	
	printf("	%f\n", (double)(bestMove->score) / 100);
	
	return 0;
}
