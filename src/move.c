#include "chengine.h"


// Move format

/*
  
 0000 0001 1111 1100 0000 0000 0000		source square		0x1fc000
 0000 0000 0000 0011 1111 1000 0000		target square		0x3f80
 0000 0000 0000 0000 0000 0111 1000		promoted piece		0x78
 0000 0000 0000 0000 0000 0000 0100		pawn start flag		0x4
 0000 0000 0000 0000 0000 0000 0010		en passant flag		0x2
 0000 0000 0000 0000 0000 0000 0001		castling flag		0x1

*/

void SetMove(MOVE *move, int fromSq, int toSq, int promPiece, int pawnFlag, int enPassantFlag, int castleFlag)
{
	assert(!(fromSq & 0x88));
	assert(!(toSq & 0x88));
	assert((promPiece >= wN && promPiece <= wQ) || (promPiece >= bN && promPiece <= bQ));
	
	move->move |= fromSq;
	move->move <<= 7;
	
	move->move |= toSq;
	move->move <<= 4;
	
	move->move |= promPiece;
	move->move <<= 1;
	
	move->move |= pawnFlag;
	move->move <<= 1;
	
	move->move |= enPassantFlag;
	move->move <<= 1;
	
	move->move |= castleFlag;
}


int GetMoveSource(MOVE *move)
{
	int fromSq;
	
	fromSq = move->move & 0x1fc000;
	fromSq >>= 14;
	
	return fromSq;
}


int GetMoveTarget(MOVE *move)
{
	int toSq;
	
	toSq = move->move & 0x3f80;
	toSq >>= 7;
	
	return toSq;
}


int GetMovePromPiece(MOVE *move)
{
	int promPiece;
	
	promPiece = move->move & 0x78;
	promPiece >>= 3;
	
	return promPiece;
}


int GetMovePawnStartFlag(MOVE *move)
{
	int pawnStart;
	
	pawnStart = move->move & 4;
	pawnStart >>= 2;
	
	return pawnStart;
}


int GetMoveEnPassantFlag(MOVE *move)
{
	int enPassant;
	
	enPassant = move->move & 2;
	enPassant >>= 1;
	
	return enPassant;
}


int GetMoveCastleFlag(MOVE *move)
{	
	return move->move & 1;	
}


void PrintMoveBinary(MOVE *move)
{
	int fourCount = -1;

	//for(int i = 0; i < 32; ++i)
	for(int i = 31; i >= 0; i--)
	{
		fourCount++;
		
		if(fourCount == 4)
		{
			printf(" ");
			fourCount = 0;
		}
		
		if((move->move >> i) & 1)
			printf("1");
		
		else
			printf("0");
	}
	
	printf("\n");
}


void PrintMove(MOVE *move)
{
	int fromSq = GetMoveSource(move);
	int toSq = GetMoveTarget(move);
	int promPiece = GetMovePromPiece(move);
	int enPass = GetMoveEnPassantFlag(move);
	int pawnStart = GetMovePawnStartFlag(move);
	int castle = GetMoveCastleFlag(move);
	
	PrintSquare(fromSq);
	PrintSquare(toSq);
	PrintPromotedPiece(promPiece);
	
	printf("    pawn start: %d;  en passant: %d;  castle: %d\n", pawnStart, enPass, castle);
}



