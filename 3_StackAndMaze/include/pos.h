#ifndef POS_H
#define POS_H
typedef struct position
{
    int x;
    int y;
} Position;

static int offset[4][2] = {
    {-1, 0}, // ���� 0 ��
    {0, 1},  // ���� 1 ��
    {1, 0},  // ���� 2 ��
    {0, -1}  // ���� 3 ��
};

Position move_to(Position pos, int dir);
#endif