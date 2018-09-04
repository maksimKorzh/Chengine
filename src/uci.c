#include "chengine.h"

#define inputBuffer (400 * 6)

void UciLoop(CHESSBOARD *board)
{
	char line[inputBuffer];

	printf("id name chengine\n");
	printf("id author Maksim Korzh\n");
	printf("uciok\n");
	
	while(1)
	{
		memset(&line[0], 0, sizeof(line));
		fflush(stdout);
		
		if(!fgets(line, inputBuffer, stdin))
			continue;
			
		if(line[0] == '\n')
			continue;
			
		if (!strncmp(line, "uci", 3))
		{
			printf("id name chengine\n");
			printf("id author Maksim Korzh\n");
			printf("uciok\n");
		}
		
		else if(!strncmp(line, "isready", 7))
		{
			printf("readyok\n");
			continue;
		}
		
		else if (!strncmp(line, "ucinewgame", 10))
		{
			ParseFen(board, initPos);
			PrintBoard(board);
		}
		
		else if(!strncmp(line, "position startpos moves", 23))
		{
			ParseFen(board, initPos);
			PrintBoard(board);
			
			char *moves = line;
			moves += 23;
			
			int countChar = -1;
			
			while(*moves)
			{
				if(*moves == ' ')
				{
					*moves++;
					MakeMove(board, ParseMove(board, moves));
				}
				
				*moves++;
			}
			
			PrintBoard(board);
		}
		
		else if(!strncmp(line, "position startpos", 17))
		{
			ParseFen(board, initPos);
			PrintBoard(board);
		}
		
		else if(!strncmp(line, "position fen", 12))
		{
			char *fen = line;
			fen += 13;
			
			ParseFen(board, fen);
			
			char *moves = line;
			
			while(strncmp(moves, "moves", 5))
			{
				*moves++;
				
				if(*moves == '\0')
					break;
			}
			
			
			moves += 4;
			//printf("moves: \" %c \"", *moves);
			
			if(*moves == 's')
			{
				int countChar = -1;
			
				while(*moves)
				{
					if(*moves == ' ')
					{
						*moves++;
						MakeMove(board, ParseMove(board, moves));
					}
				
					*moves++;
				}
				
				PrintBoard(board);
			}
			
			else
				PrintBoard(board);
		}
		
		else if (!strncmp(line, "go depth", 8))
		{
			char *go = line;
			go += 9;
			
			int depth = *go - '0';
			
			SearchPosition(board, depth);
		}
		
		else if(!strncmp(line, "quit", 4))
			break;
			
		else
			SearchPosition(board, 4);
	}
}
