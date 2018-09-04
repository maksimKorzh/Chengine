#include "chengine.h"


int main()
{
	CHESSBOARD board[1];
	/*ParseFen(board, "rnbqkbnr/pppp1ppp/8/4p3/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 ");
	PrintBoard(board);
	printf("%d\n", EvaluatePosition(board));*/
	
	
	UciLoop(board);
	
	return 0;
}
