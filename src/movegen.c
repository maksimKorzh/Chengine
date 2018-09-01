#include "chengine.h"


void AddMove(MOVELIST *movelist, int move)
{
	movelist->moves[movelist->moveCount].move = move;
	movelist->moveCount++;
}
