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


void PrintPosition(CHESSBOARD *board)
{
	printf("\n");	
	
	for(int rank = 8; rank >= 1; rank--)
	{
		for(int file = 16; file >= 1; file--)
		{
			int sq = rank * 16 - file;
			
			board->position[sq] < 0 ?
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
	printf("     EnPassant:          %d\n", board->enPassant);
	printf("     Castling:         %c%c%c%c\n", board->castling & wk ? 'K' : '-',
												board->castling & wq ? 'Q' : '-',
												board->castling & bk ? 'k' : '-',
												board->castling & bq ? 'q' : '-');
	
	printf("\n");	
}



