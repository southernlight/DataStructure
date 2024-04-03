#include "pos.h"

//���θ� x ���θ� y�� �д�.
Position move_to(Position pos, int dir) //���� ��ġ pos���� dir �������� ��ĭ �̵��� ��ġ
{
    Position next;
    next.x = pos.x + offset[dir][0];
    next.y = pos.y + offset[dir][1];

    return next;
}