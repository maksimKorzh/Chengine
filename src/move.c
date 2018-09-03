#include "chengine.h"


// Move format

/*
  
 0001 1111 1100 0000 0000 0000		source square		0x1fc000
 0000 0000 0011 1111 1000 0000		target square		0x3f80
 0000 0000 0000 0000 0111 1000		promoted piece		0x78
 0000 0000 0000 0000 0000 0100		pawn start flag		0x4
 0000 0000 0000 0000 0000 0010		en passant flag		0x2
 0000 0000 0000 0000 0000 0001		castling flag		0x1

*/

int SetMove(int fromSq, int toSq, int promPiece, int pawnFlag, int enPassantFlag, int castleFlag)
{
	assert(!(fromSq & 0x88));
	assert(!(toSq & 0x88));
	assert((promPiece >= wN && promPiece <= wQ) || (promPiece >= bN && promPiece <= bQ) || promPiece == 0);
	
	int move = 0;
	
	move |= fromSq;
	move <<= 7;
	
	move |= toSq;
	move <<= 4;
	
	move |= promPiece;
	move <<= 1;
	
	move |= pawnFlag;
	move <<= 1;
	
	move |= enPassantFlag;
	move <<= 1;
	
	move |= castleFlag;
	
	return move;
}


int GetMoveSource(int move)
{
	int fromSq;
	
	fromSq = move & 0x1fc000;
	fromSq >>= 14;
	
	return fromSq;
}


int GetMoveTarget(int move)
{
	int toSq;
	
	toSq = move & 0x3f80;
	toSq >>= 7;
	
	return toSq;
}


int GetMovePromPiece(int move)
{
	int promPiece;
	
	promPiece = move & 0x78;
	promPiece >>= 3;
	
	return promPiece;
}


int GetMovePawnStartFlag(int move)
{
	int pawnStart;
	
	pawnStart = move & 4;
	pawnStart >>= 2;
	
	return pawnStart;
}


int GetMoveEnPassantFlag(int move)
{
	int enPassant;
	
	enPassant = move & 2;
	enPassant >>= 1;
	
	return enPassant;
}


int GetMoveCastleFlag(int move)
{	
	return move & 1;	
}


void PrintMoveBinary(int move)
{
	int fourCount = -1;

	for(int i = 31; i >= 0; i--)
	{
		fourCount++;
		
		if(fourCount == 4)
		{
			printf(" ");
			fourCount = 0;
		}
		
		if((move >> i) & 1)
			printf("1");
		
		else
			printf("0");
	}
	
	printf("\n");
}


void PrintMove(int move)
{
	int fromSq = GetMoveSource(move);
	int toSq = GetMoveTarget(move);
	int promPiece = GetMovePromPiece(move);
	int enPass = GetMoveEnPassantFlag(move);
	int pawnStart = GetMovePawnStartFlag(move);
	int castle = GetMoveCastleFlag(move);
	
	printf("  ");
	
	PrintSquare(fromSq);
	PrintSquare(toSq);
	PrintPromotedPiece(promPiece);
	
	//printf("	  pawn start: %d;  en passant: %d;  castle: %d", pawnStart, enPass, castle);
}


void PrintMoveList(MOVELIST *movelist)
{
	for(int moveCount = 0; moveCount < movelist->moveCount; ++moveCount)
	{
		PrintMove(movelist->moves[moveCount].move);
		printf("	SCORE: %d\n", movelist->moves[moveCount].score);
	}
	
	printf("\n  Total moves: %d\n\n", movelist->moveCount);
}


