#include "chengine.h"


void InitBoard(CHESSBOARD *board)
{
	for(int rank = 0; rank < 8; ++rank)
	{
		for(int file = 0; file < 16; ++file)
		{
			int sq = rank * 16 + file;
			
			if(file < 8)
			{
				assert(!(sq & 0x88));
				board->position[sq] = emSq;
			}
			
			else
				board->position[sq] = 8;
		}
	}
	
	board->side = -1;
	board->enPassant = noSq;
	board->castling = 0;
}


void ParseFen(CHESSBOARD *board, char *fen)
{
	InitBoard(board);

	for(int rank = 8; rank >= 1; rank--)
	{
		for(int file = 16; file >= 1; file--)
		{
			int sq = rank * 16 - file;
			
			if(file > 8)
			{
				assert(!(sq & 0x88));
				
			
				switch(*fen)
				{
					case 'P': board->position[sq] = wP; *fen++; break;
					case 'N': board->position[sq] = wN; *fen++; break;
					case 'B': board->position[sq] = wB; *fen++; break;
					case 'R': board->position[sq] = wR; *fen++; break;
					case 'Q': board->position[sq] = wQ; *fen++; break;
					case 'K': board->position[sq] = wK; *fen++; break;
		
					case 'p': board->position[sq] = bP; *fen++; break;
					case 'n': board->position[sq] = bN; *fen++; break;
					case 'b': board->position[sq] = bB; *fen++; break;
					case 'r': board->position[sq] = bR; *fen++; break;
					case 'q': board->position[sq] = bQ; *fen++; break;
					case 'k': board->position[sq] = bK; *fen++; break;
				}
				
				if(*fen >= '0' && *fen <= '9')
				{
					int count = *fen - '0';
			
					if(board->position[sq] == 0)
						file++;
			
					/*for(int i = 0; i < count; ++i)
					{	
						file--;
						
						int empty = rank * 16 - file;
						board->position[empty] = emSq;	
					}*/
					
					file -= count;
					
					*fen++;
				}
			
				if(*fen == '/')
				{
					*fen++;
					file--;
				}
			}
		}
	}
	
	*fen++;
	
	assert(*fen == 'w' || *fen == 'b');
	board->side = (*fen == 'w') ? white : black;
	
	fen += 2;

	while(*fen != ' ')
	{
		switch(*fen)
		{
			case 'K': board->castling |= wk; break;
			case 'Q': board->castling |= wq; break;
			case 'k': board->castling |= bk; break;
			case 'q': board->castling |= bq; break;
			
			case '-': board->castling = 0;
        }
        
		fen++;
	}
	
	fen++;
	
	if(*fen != '-')
	{
		int file = fen[0] - 'a';
		int rank = fen[1] - '0';
		
		int enPassant = (rank - 1) * 16 + file;
		assert(!(enPassant & 0x88));
		
		board->enPassant = enPassant;
	}
}


int ParseMove(CHESSBOARD *board, char *moveStr)
{
	MOVELIST list[1];
	GenerateMoves(board, list);

	int parseFrom = (moveStr[0] - 'a') + (moveStr[1] - '0' - 1) * 16;
	int parseTo = (moveStr[2] - 'a') + (moveStr[3] - '0' - 1) * 16;
	int promPiece = 0;
	
	int move;
	
	for(int moveNum = 0; moveNum < list->moveCount; ++moveNum)
	{
		move = list->moves[moveNum].move;
		
		if(GetMoveSource(move) == parseFrom && GetMoveTarget(move) == parseTo)
		{
			promPiece = GetMovePromPiece(move);
			
			if(promPiece)
			{	
				if((promPiece == wN || promPiece == bN) && moveStr[4] == 'n')
					return move;
					
				else if((promPiece == wB || promPiece == bB) && moveStr[4] == 'b')
					return move;
					
				else if((promPiece == wR || promPiece == bR) && moveStr[4] == 'r')
					return move;
					
				else if((promPiece == wQ || promPiece == bQ) && moveStr[4] == 'q')
					return move;
					
				continue;
			}
		
			return move;
		}
	}
	
	return 0;
}


void PrintSquare(int sq)
{
	assert((sq == -99) || !(sq & 0x88));
	
	if(sq == -99)
	{
		printf("no");
		return;
	}
	
	char file = (sq & 7) + 'a';
	char rank = (sq >> 4) + '1';
	
	printf("%c%c", file, rank);
}


void PrintPromotedPiece(int piece)
{
	assert((piece >= wN && piece <= wQ) || (piece >= bN && piece <= bQ) || piece == 0);
	
	switch(piece)
	{
		case wN:
		case bN: printf("n"); break;
		
		case wB:
		case bB: printf("b"); break;
		
		case wR:
		case bR: printf("r"); break;
		
		case wQ:
		case bQ: printf("q"); break;
		
		default: break;
	}
	
}


void PrintPosition(CHESSBOARD *board)
{
	printf("\n");	
	
	for(int rank = 8; rank >= 1; rank--)
	{
		for(int file = 16; file >= 1; file--)
		{
			int sq = rank * 16 - file;
			
			board->position[sq] > 9 ?
				printf(" %d", board->position[sq]) : printf("  %d", board->position[sq]);
		}
		
		printf("\n");
	}
	
	printf("\n\n");
}


void PrintBoard(CHESSBOARD *board)
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
				
				switch(board->position[sq])
				{
					case wP: printf("  %s", "\u2659"); break;
					case wN: printf("  %s", "\u2658"); break;
					case wB: printf("  %s", "\u2657"); break;
					case wR: printf("  %s", "\u2656"); break;
					case wQ: printf("  %s", "\u2655"); break;
					case wK: printf("  %s", "\u2654"); break;
		
					case bP: printf("  %s", "\u265F"); break;
					case bN: printf("  %s", "\u265E"); break;
					case bB: printf("  %s", "\u265D"); break;
					case bR: printf("  %s", "\u265C"); break;
					case bQ: printf("  %s", "\u265B"); break;
					case bK: printf("  %s", "\u265A"); break;
					
					case emSq: printf("  ."); break;
				}
			}
		}
		
		printf("\n");
	}
	
	printf("\n     a  b  c  d  e  f  g  h\n\n");
	
	printf("     Side:            %s\n", board->side == white ? "white" : "black");
	
	printf("     EnPassant:          ");
	PrintSquare(board->enPassant);
	printf("\n");
	
	printf("     Castling:         %c%c%c%c\n", board->castling & wk ? 'K' : '-',
												board->castling & wq ? 'Q' : '-',
												board->castling & bk ? 'k' : '-',
												board->castling & bq ? 'q' : '-');
	
	printf("\n\n");	
}



