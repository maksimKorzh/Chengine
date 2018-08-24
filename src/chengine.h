#ifndef CHENGINE
#define CHENGINE


#include <stdio.h>


#define DEBUG

#ifdef DEBUG
	#include <assert.h>
#endif


#define  initPos "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 "
#define  trickyPos "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1 "

enum side
{
	white,
	black
};

enum pieces
{
	emSq = 0,
	
	wP = 1,
	wN = 2,
	wB = 3,
	wR = 4,
	wQ = 5,
	wK = 6,
	
	bP = -1,
	bN = -2,
	bB = -3,
	bR = -4,
	bQ = -5,
	bK = -6
};

enum squares
{
	a1 = 0, b1, c1, d1, e1, f1, g1, h1,
	a2 = 16, b2, c2, d2, e2, f2, g2, h2,
	a3 = 32, b3, c3, d3, e3, f3, g3, h3,
	a4 = 48, b4, c4, d4, e4, f4, g4, h4,
	a5 = 64, b5, c5, d5, e5, f5, g5, h5,
	a6 = 80, b6, c6, d6, e6, f6, g6, h6,
	a7 = 96, b7, c7, d7, e7, f7, g7, h7,
	a8 = 112, b8, c8, d8, e8, f8, g8, h8
};

enum castling
{
	wk = 1,
	wq = 2,
	bk = 4,
	bq = 8
};

typedef struct
{
	int position[128];
	
	int side;
	int enPassant;
	int castling;
}

CHESSBOARD;


// functions

// board.c
void InitBoard(CHESSBOARD *board);
void ParseFen(CHESSBOARD *board, char *fen);
void PrintPosition(CHESSBOARD *board);
void PrintBoard(CHESSBOARD *board);


#endif
