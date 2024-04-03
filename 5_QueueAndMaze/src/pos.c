#include "pos.h"

Position move_to(Position pos, int dir)
{
	Position next;
	next.x = pos.x + offset[dir][0];
	next.y = pos.y + offset[dir][1];
	return next;
}