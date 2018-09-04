#include "chengine.h"

int NegaMaxSearch(CHESSBOARD *board, int depth)
{
	if(InCheck(board, board->side))
		depth++;

	if ( depth == 0 )
		return EvaluatePosition(board);	
	
	int legalMoves = 0;
	int bestScore = -50000;
	
	MOVELIST list[1];
	GenerateMoves(board, list);
	
	for(int moveNum = 0; moveNum < list->moveCount; ++moveNum)
	{
		CHESSBOARD boardStored[1];
		boardStored[0] = board[0];
		
		if(!MakeMove(board, list->moves[moveNum].move))
			continue;
		
		legalMoves++;
		int score = -NegaMaxSearch(board, depth - 1);
		
		if(score > bestScore)
			bestScore = score;
			
		TakeBack(board, boardStored);
	}
	
	// checkmate detection
	if(!legalMoves && InCheck(board, board->side))
		return -100000;
	else
		return bestScore;
}

void SearchPosition(CHESSBOARD *board, int depth)
{
	int bestScore = -50000;
	int legalMoves = 0;

	MOVELIST list[1];
	GenerateMoves(board, list);
	
	MOVE bestMove;
	
	for(int moveNum = 0; moveNum < list->moveCount; ++moveNum)
	{
		CHESSBOARD boardStored[1];
		boardStored[0] = board[0];
		
		if(!MakeMove(board, list->moves[moveNum].move))
			continue;
			
		legalMoves++;	
		int score = -NegaMaxSearch(board, depth - 1);
		
		if(score > bestScore)
		{
			bestScore = score;
		
			
			bestMove.move = list->moves[moveNum].move;
			bestMove.score = bestScore;	
		}
		
		TakeBack(board, boardStored);
	}
	
	if(legalMoves)
	{
		printf("info score cp %d depth %d\n", bestMove.score, depth);
	
		printf("bestmove ");
		PrintMove(bestMove.move);
		printf("\n");
	}	
}



