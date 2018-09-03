#include "chengine.h"


long nodes;

void Perft(CHESSBOARD *board, int depth)
{
	if(depth == 0)
	{
		nodes++;
		return;
	}
	
	MOVELIST list[1];
	GenerateMoves(board, list);
	
	for(int moveNum = 0; moveNum < list->moveCount; ++moveNum)
	{
		CHESSBOARD boardStored[1];
		boardStored[0] = board[0];
	
		if(!MakeMove(board, list->moves[moveNum].move))
			continue;
		
		//getchar();
		//PrintBoard(board);
		//PrintMoveList(list);
			
		Perft(board, depth - 1);
		TakeBack(board, boardStored);
	}
}


void PerftTest(CHESSBOARD *board, int depth)
{
	PrintBoard(board);
	
	printf("\n  Perft to depth: %d\n\n",depth);
		
	nodes = 0;
	
	int start = GetTimeMs();
	
	MOVELIST list[1];
	GenerateMoves(board, list);
	
	int move;
	
	for(int moveNum = 0; moveNum < list->moveCount; ++moveNum)
	{
		move = list->moves[moveNum].move;
		
		CHESSBOARD boardStored[1];
		boardStored[0] = board[0];
		
		if(!MakeMove(board, move))
			continue;	
		
		if(GetMoveSource(list->moves[moveNum].move) == a7 && GetMoveTarget(list->moves[moveNum].move) == a6)	
			PrintBoard(board);
		
		long cumnodes = nodes;
		
		Perft(board, depth - 1);
		TakeBack(board, boardStored);
		
		long oldnodes = nodes - cumnodes;
		
		printf("  move %d:	", moveNum + 1);
		PrintMove(move);
		printf(": %ld\n", oldnodes);
    }
	
	printf("\n  Test Complete : %ld nodes visited in %dms\n\n", nodes, GetTimeMs() - start);
	
	return;
}
