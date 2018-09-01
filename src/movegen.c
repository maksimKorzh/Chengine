#include "chengine.h"


#define isBlackPiece(toSq) (board->position[toSq] >= bP && board->position[toSq] <= bK)


void AddMove(MOVELIST *list, int move)
{
	list->moves[list->moveCount].move = move;
	list->moves[list->moveCount].score = 0;
	list->moveCount++;
}


void GenerateMoves(CHESSBOARD *board, MOVELIST *list)
{
	int side = board->side;
	
	for(int sq = 0; sq < 128; ++sq)
	{
		if(!(sq & 0x88))
		{
			if(side == white && board->position[sq] == wP)
			{
				int fromSq = sq;
				
				//capture move
				if(!((fromSq + 15) & 0x88) && isBlackPiece(fromSq + 15))
				{
					PrintSquare(fromSq);
					PrintSquare(fromSq + 15);
			
					printf("\n");
				}
			
				if(!((fromSq + 17) & 0x88) && isBlackPiece(fromSq + 17))
				{
					PrintSquare(fromSq);
					PrintSquare(fromSq + 17);
			
					printf("\n");
				}
			}
		}	
	}
}
