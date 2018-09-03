#include "chengine.h"


const int pawnAttacks[4] = {15, 17, -15, -17};
const int knightAttacks[8] = {31, 33, 14, 18, -31, -33, -14, -18};
const int kingAttacks[8] = {1, 15, 16, 17, -1, -15, -16, -17};
const int bishopAttacks[4] = {15, 17, -15, -17};
const int rookAttacks[4] = {1, 16, -1, -16};

int IsSquareAttacked(CHESSBOARD *board, int sq, int side)
{
	assert(!(sq & 0x88));

	// by pawns
	if(side == white)
	{
		if(!((sq - 15) & 0x88) && (board->position[sq - 15] == wP))
			return 1;
			
		if(!((sq - 17) & 0x88) && (board->position[sq - 17] == wP))
			return 1;
	}
	
	else
	{
		if(!((sq + 15) & 0x88) && (board->position[sq + 15] == bP))
			return 1;
			
		if(!((sq + 17) & 0x88) && (board->position[sq + 17] == bP))
			return 1;
	}

	// by knights
	for(int i = 0; i < 8; ++i)
	{
		int dir = sq + knightAttacks[i];
		int delta = board->position[dir];
		
		if(!(dir & 0x88))
		{
			if(side ? delta == bN : delta == wN)
			{
				assert(!(dir & 0x88));
				return 1;
			}
		}
	}
	
	
	// by bishops and queens
	for(int i = 0; i < 4; ++i)
	{
		int dir = sq + bishopAttacks[i];
		
		while(!(dir & 0x88))
		{
			int delta = board->position[dir];
			
			if(side ? (delta == bB) || (delta == bQ) : (delta == wB) || (delta == wQ))
			{
				return 1;
			}
			
			else if(delta != 0)
				break;
			
			dir += bishopAttacks[i];
		}
	}
	
	
	// by rooks and queens
	for(int i = 0; i < 4; ++i)
	{
		int dir = sq + rookAttacks[i];
		
		while(!(dir & 0x88))
		{
			int delta = board->position[dir];
			
			if(side ? (delta == bR) || (delta == bQ) : (delta == wR) || (delta == wQ))
			{
				return 1;
			}
			
			else if(delta != 0)
				break;
			
			dir += rookAttacks[i];
		}
	}
	
	
	// by kings
	for(int i = 0; i < 8; ++i)
	{
		int dir = sq + kingAttacks[i];
		int delta = board->position[dir];
		
		if(!(dir & 0x88))
		{
			if(side ? delta == bK : delta == wK)
			{
				assert(!(dir & 0x88));
				return 1;
			}
		}
	}

	return 0;
}


void PrintAttackBoard(CHESSBOARD *board, int side)
{
	printf("\n");	
	
	for(int rank = 8; rank >= 1; rank--)
	{
		printf("  %d", rank);
	
		for(int file = 16; file >= 1; file--)
		{
			int sq = rank * 16 - file;
			
			if(file > 8)
			{
				assert(!(sq & 0x88));
				
				if(IsSquareAttacked(board, sq, side))
					printf("  x");
					
				else
					printf("  .");
			}
		}
		
		printf("\n");
	}
	
	printf("\n     a  b  c  d  e  f  g  h\n\n");
}
