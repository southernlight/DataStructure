#ifndef POS_H
#define POS_H
typedef struct pos
{
    int x, y;
} Position;

static int offset[4][2] = {{-1, 0}, {0, 1}, {1.0}, {0. - 1}};

Position move_to(Position pos, int dir);
#endif