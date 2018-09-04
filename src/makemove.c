#include "chengine.h"


#define isBlack(toSq) (board->position[toSq] >= bN && board->position[toSq] <= bQ)
#define isWhite(toSq) (board->position[toSq] >= wN && board->position[toSq] <= wQ)


const int castling[128] = 
{
	13, 15, 15, 15, 12, 15, 15, 14, 8, 8, 8, 8, 8, 8, 8, 8,
	15, 15, 15, 15, 15, 15, 15, 15, 8, 8, 8, 8, 8, 8, 8, 8,
	15, 15, 15, 15, 15, 15, 15, 15, 8, 8, 8, 8, 8, 8, 8, 8,
	15, 15, 15, 15, 15, 15, 15, 15, 8, 8, 8, 8, 8, 8, 8, 8,
	15, 15, 15, 15, 15, 15, 15, 15, 8, 8, 8, 8, 8, 8, 8, 8,
	15, 15, 15, 15, 15, 15, 15, 15, 8, 8, 8, 8, 8, 8, 8, 8,
	15, 15, 15, 15, 15, 15, 15, 15, 8, 8, 8, 8, 8, 8, 8, 8,
	 7, 15, 15, 15,  3, 15, 15, 11, 8, 8, 8, 8, 8, 8, 8, 8
};


int InCheck(CHESSBOARD *board, int side)
{
	int kingSq = noSq;

	for(int sq = 0; sq < 128; ++sq)
	{
		if(side ? board->position[sq] == bK : board->position[sq] == wK)
		{
			kingSq = sq;
			break;
		}
	}
	
	return IsSquareAttacked(board, kingSq, side ^ 1);
}

int UnderAttack(CHESSBOARD *board, int side)
{
	int attackedPiece = noSq;

	for(int sq = 0; sq < 128; ++sq)
	{
		if(side ? isBlack(sq) : isWhite(sq))
		{
			attackedPiece = sq;
			break;
		}
	}
	
	return IsSquareAttacked(board, attackedPiece, side ^ 1);
}


int MakeMove(CHESSBOARD *board, int move)
{
	CHESSBOARD boardStored[1];
	boardStored[0] = board[0];

	int fromSq = GetMoveSource(move);
	int toSq = GetMoveTarget(move);
	int side = board->side;

	// move piece
	board->position[toSq] = board->position[fromSq];
	board->position[fromSq] = emSq;
	
	// promotions
	if(GetMovePromPiece(move))
	{
		board->position[toSq] = GetMovePromPiece(move);
		board->position[fromSq] = emSq;
	}
		
	// en passant flag
	if(GetMoveEnPassantFlag(move))
	{
		board->side ? 
			(board->position[board->enPassant + 16] = 0) :
			(board->position[board->enPassant - 16] = 0);
			
		board->enPassant = noSq;
	}
	
	board->enPassant = noSq;
	
	// pawn start flag
	if(GetMovePawnStartFlag(move))
	{
		board->side ?
			(board->enPassant = toSq + 16) :
			(board->enPassant = toSq - 16);
	}
	
	// castling flag
	if(GetMoveCastleFlag(move))
	{
		switch(toSq)
		{
			case g1:
				board->position[f1] = board->position[h1];
				board->position[h1] = emSq;
				break;
				
			case c1:
				board->position[d1] = board->position[a1];
				board->position[a1] = emSq;
				break;
				
			case g8:
				board->position[f8] = board->position[h8];
				board->position[h8] = emSq;
				break;
				
			case c8:
				board->position[d8] = board->position[a8];
				board->position[a8] = emSq;
				break;
		}
	}
	
	// update castling permission
	board->castling &= castling[fromSq];
	board->castling &= castling[toSq];
	
	// change side
	board->side = side ^ 1;
	
	// in check
	if(InCheck(board, side))
	{
		TakeBack(board, boardStored);
		return 0;
	}
	
	else
		return 1;
}


void TakeBack(CHESSBOARD *board, CHESSBOARD *boardStored)
{
	board[0] = boardStored[0];
}


