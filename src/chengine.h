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
	
	bP = 9,
	bN = 10,
	bB = 11,
	bR = 12,
	bQ = 13,
	bK = 14
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
	a8 = 112, b8, c8, d8, e8, f8, g8, h8,
	
	noSq = -99
};

enum castling
{
	wk = 1,
	wq = 2,
	bk = 4,
	bq = 8
};


// Move format

/*

 0000 0000 0111 1111	fromSq     (0x7f)
 0011 1111 1000 0000	toSq >> 7, (0x3f)
*/

typedef struct
{
	unsigned int move;
	int score;
}

MOVE;

typedef struct
{
	MOVE move[256];
	int count;
}

MOVELIST;


typedef struct
{
	int position[128];
	
	int side;
	int enPassant;
	int castling;
}

CHESSBOARD;

extern int knightAttacks[8];
extern int kingAttacks[8];
extern int bishopAttacks[4];
extern int rookAttacks[4];

// functions

// board.c
extern void InitBoard(CHESSBOARD *board);
extern void PrintSquare(int sq);
extern void PrintMove(unsigned int move);
extern void PrintMoveBinary(unsigned int move);
extern void ParseFen(CHESSBOARD *board, char *fen);
extern void PrintPosition(CHESSBOARD *board);
extern void PrintBoard(CHESSBOARD *board);

// attack.c
extern int IsSquareAttacked(CHESSBOARD *board, int sq, int side);
extern void PrintAttackBoard(CHESSBOARD *board, int side);


#endif



