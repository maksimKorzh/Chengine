#include "chengine.h"

const int materialWeight[15] = 
{
	0, 100, 350, 350, 525, 1000, 10000, 0,
	0, -100, -350, -350, -525, -1000, -10000
};


int EvaluatePosition(CHESSBOARD *board)
{
	int score = 0;
	
	// count material
	for(int sq = 0; sq < 128; ++sq)
	{
		if(!(sq & 0x88))
		{
			if(board->position[sq])
			{
				int piece = board->position[sq];
				score += materialWeight[piece];
			}
		}
	}
	
	if(board->side == white)
		return score;
		
	else
		return -score;
}
