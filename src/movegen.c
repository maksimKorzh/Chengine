#include "chengine.h"


#define isBlackPiece(toSq) (board->position[toSq] >= bP && board->position[toSq] <= bK)
#define isWhitePiece(toSq) (board->position[toSq] >= wP && board->position[toSq] <= wK)


static void AddMove(MOVELIST *list, int move)
{
	list->moves[list->moveCount].move = move;
	list->moves[list->moveCount].score = 0;
	list->moveCount++;
}


void GenerateMoves(CHESSBOARD *board, MOVELIST *list)
{
	int side = board->side;
	
	list->moveCount = 0;
	
	for(int sq = 0; sq < 128; ++sq)
	{
		if(!(sq & 0x88))
		{
			int fromSq = sq;
			
			if(side == white)
			{	
				if(board->position[fromSq] == wP)
				{
					// pawn quiet move
					if(!((fromSq + 16) & 0x88) && board->position[fromSq + 16] == emSq)
					{
						if((fromSq >= a7 && fromSq <= h7) && board->position[fromSq + 16] == emSq)
						{
							AddMove(list, SetMove(fromSq, fromSq + 16, wN, 0, 0, 0));
							AddMove(list, SetMove(fromSq, fromSq + 16, wB, 0, 0, 0));
							AddMove(list, SetMove(fromSq, fromSq + 16, wR, 0, 0, 0));
							AddMove(list, SetMove(fromSq, fromSq + 16, wQ, 0, 0, 0));
						}
					
						else
						{
							AddMove(list, SetMove(fromSq, fromSq + 16, 0, 0, 0, 0));
					
							if((fromSq >= a2 && fromSq <= h2) && board->position[fromSq + 32] == emSq)
							{
								AddMove(list, SetMove(fromSq, fromSq + 32, 0, 1, 0, 0));
							}
						}
					}
				
					// pawn capture move
					for(int i = 0; i < 4; ++i)
					{
						int dir = fromSq + pawnAttacks[i];
					
						// en passant move
						if(board->enPassant != noSq)
						{
							if(dir == board->enPassant)
								AddMove(list, SetMove(fromSq, dir, 0, 0, 1, 0));
						}
					
						if((pawnAttacks[i] > 0) && !(dir & 0x88) && isBlackPiece(dir))
						{
							if(fromSq >= a7 && fromSq <= h7)
							{
								AddMove(list, SetMove(fromSq, dir, wN, 0, 0, 0));
								AddMove(list, SetMove(fromSq, dir, wB, 0, 0, 0));
								AddMove(list, SetMove(fromSq, dir, wR, 0, 0, 0));
								AddMove(list, SetMove(fromSq, dir, wQ, 0, 0, 0));
							
							}
						
							else
							{
								AddMove(list, SetMove(fromSq, dir, 0, 0, 0, 0));
							}
						}
					}
				}
			
				// castling
				if(board->position[fromSq] == wK)
				{
					if(board->castling & wk)
					{
						if(board->position[f1] == emSq && board->position[g1] == emSq)
						{
							if(!IsSquareAttacked(board, e1, black) && !IsSquareAttacked(board, f1, black))
								AddMove(list, SetMove(e1, g1, 0, 0, 0, 1));
						}
					}
					
					if(board->castling & wq)
					{
						if(board->position[d1] == emSq && board->position[c1] == emSq && board->position[b1] == emSq)
						{
							if(!IsSquareAttacked(board, e1, black) && !IsSquareAttacked(board, d1, black))
								AddMove(list, SetMove(e1, c1, 0, 0, 0, 1));
						}
					}
				}
			}
			
			else
			{	
				if(board->position[fromSq] == bP)
				{
					// pawn quiet move
					if(!((fromSq - 16) & 0x88) && board->position[fromSq - 16] == emSq)
					{
						if((fromSq >= a2 && fromSq <= h2) && board->position[fromSq - 16] == emSq)
						{
							AddMove(list, SetMove(fromSq, fromSq - 16, bN, 0, 0, 0));
							AddMove(list, SetMove(fromSq, fromSq - 16, bB, 0, 0, 0));
							AddMove(list, SetMove(fromSq, fromSq - 16, bR, 0, 0, 0));
							AddMove(list, SetMove(fromSq, fromSq - 16, bQ, 0, 0, 0));
						}
					
						else
						{
							AddMove(list, SetMove(fromSq, fromSq - 16, 0, 0, 0, 0));
					
							if((fromSq >= a7 && fromSq <= h7) && board->position[fromSq - 32] == emSq)
							{
								AddMove(list, SetMove(fromSq, fromSq - 32, 0, 1, 0, 0));
							}
						}
					}
				
					// pawn capture move
					for(int i = 0; i < 4; ++i)
					{
						int dir = fromSq + pawnAttacks[i];
					
						// en passant move
						if(board->enPassant != noSq)
						{
							if(dir == board->enPassant)
								AddMove(list, SetMove(fromSq, dir, 0, 0, 1, 0));
						}
					
						if((pawnAttacks[i] < 0) && !(dir & 0x88) && isWhitePiece(dir))
						{
							if(fromSq >= a2 && fromSq <= h2)
							{
								AddMove(list, SetMove(fromSq, dir, bN, 0, 0, 0));
								AddMove(list, SetMove(fromSq, dir, bB, 0, 0, 0));
								AddMove(list, SetMove(fromSq, dir, bR, 0, 0, 0));
								AddMove(list, SetMove(fromSq, dir, bQ, 0, 0, 0));
							
							}
						
							else
							{
								AddMove(list, SetMove(fromSq, dir, 0, 0, 0, 0));
							}
						}
					}
				}
				
				// castling
				if(board->position[fromSq] == bK)
				{	
					if(board->castling & bk)
					{
						if(board->position[f8] == emSq && board->position[g8] == emSq)
						{
							if(!IsSquareAttacked(board, e8, white) && !IsSquareAttacked(board, f8, white))
								AddMove(list, SetMove(e8, g8, 0, 0, 0, 1));
						}
					}
				
					if(board->castling & bq)
					{
						if(board->position[d8] == emSq && board->position[c8] == emSq && board->position[b8] == emSq)
						{
							if(!IsSquareAttacked(board, e8, white) && !IsSquareAttacked(board, d8, white))
								AddMove(list, SetMove(e8, c8, 0, 0, 0, 1));
						}
					}
				}
			}
			
			// knights
			if(side ? board->position[fromSq] == bN : board->position[fromSq] == wN)
			{
				for(int i = 0; i < 8; ++i)
				{
					int dir = sq + knightAttacks[i];
					int delta = board->position[dir];
		
					if(!(dir & 0x88))
					{
						if(side ? (delta == emSq || isWhitePiece(dir)) : (delta == emSq || isBlackPiece(dir)))
						{
							AddMove(list, SetMove(fromSq, dir, 0, 0, 0, 0));
						}
					}
				}
			}
			
			// bishops and queens
			if(	side ? 
					(board->position[fromSq] == bB) || (board->position[fromSq] == bQ) :
					(board->position[fromSq] == wB) || (board->position[fromSq] == wQ)
			)
			
			{
				for(int i = 0; i < 4; ++i)
				{
					int dir = sq + bishopAttacks[i];
		
					while(!(dir & 0x88))
					{
						int delta = board->position[dir];
			
						if(side ? isBlackPiece(dir) : isWhitePiece(dir))
							break;
								
						else if(side ? isWhitePiece(dir) : isBlackPiece(dir))
						{
							AddMove(list, SetMove(fromSq, dir, 0, 0, 0, 0));
							break;
						}
			
						else if(delta == emSq)
						{		
							AddMove(list, SetMove(fromSq, dir, 0, 0, 0, 0));
						}
			
						dir += bishopAttacks[i];
					}
				}
			}
			
			// rooks and queens
			if( side ? 
					(board->position[fromSq] == bR) || (board->position[fromSq] == bQ) :
					(board->position[fromSq] == wR) || (board->position[fromSq] == wQ)
			)
			
			{
				for(int i = 0; i < 4; ++i)
				{
					int dir = sq + rookAttacks[i];
		
					while(!(dir & 0x88))
					{
						int delta = board->position[dir];
			
						if(side ? isBlackPiece(dir) : isWhitePiece(dir))
							break;
								
						else if(side ? isWhitePiece(dir) : isBlackPiece(dir))
						{
							AddMove(list, SetMove(fromSq, dir, 0, 0, 0, 0));
							break;
						}
			
						else if(delta == emSq)
						{		
							AddMove(list, SetMove(fromSq, dir, 0, 0, 0, 0));
						}
			
						dir += rookAttacks[i];
					}
				}
			}
			
			// kings
			if(side ? board->position[fromSq] == bK : board->position[fromSq] == wK)
			{
				for(int i = 0; i < 8; ++i)
				{
					int dir = sq + kingAttacks[i];
					int delta = board->position[dir];
		
					if(!(dir & 0x88))
					{
						if(side ? (delta == emSq || isWhitePiece(dir)) : (delta == emSq || isBlackPiece(dir)))
						{
							AddMove(list, SetMove(fromSq, dir, 0, 0, 0, 0));
						}
					}
				}
			}
		}	
	}
}
