#define _CRT_SECURE_NO_WARNINGS

#include "pos.h"
#include "queueADT.h"
#include <stdio.h>

#define MAX 100

int maze[MAX][MAX];
int n, m;

int read_maze();
bool movable(Position pos, int dir);
void print_maze();

int main()
{
    read_maze();

    Queue queue = create();
    Position cur;
    cur.x = 0;
    cur.y = 0;

    enqueue(queue, cur);

    maze[0][0] = -1;
    bool found = false;

    while (!is_empty(queue) && found != true)
    {
        cur = dequeue(queue);
        for (int dir = 0; dir < 4; dir++)
        {
            if (movable(cur, dir))
            {
                Position p = move_to(cur, dir);
                maze[p.x][p.y] = maze[cur.x][cur.y] - 1;
                if (p.x == n - 1 && p.y == m - 1)
                {
                    printf("Found the path.\n");
                    bool found = true;
                    break;
                }

                enqueue(queue, p);
            }
        }
    }

    print_maze();
    printf("%d\n", maze[n - 1][m - 1] * (-1));
}

bool movable(Position pos, int dir)
{
    pos.x += offset[dir][0];
    pos.y += offset[dir][1];

    if ((pos.x >= 0 && pos.x < n) && (pos.y >= 0 && pos.y <= m))
    {
        if (maze[pos.x][pos.y] == 0)
            return true;
        else
            return false;
    }

    else
        return false;
}

int read_maze()
{
    char ch;
    int row = 0, col = 0;

    FILE *fp = fopen("maze.txt", "r");
    if (fp == NULL)
        return 0;
    fscanf(fp, "%d %d", &n, &m);

    while (fgetc(fp) != '\n')
        continue;

    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
        {
            col = 0;
            row++;
        }
        else
        {
            if (ch == '0')
                maze[row][col] = '1' - '0';
            if (ch == '1')
                maze[row][col] = '0' - '0';
            col++;
        }
    }

    return 1;
}

void print_maze()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (maze[i][j] == 2)
                printf("*");
            else
                printf("%d ", maze[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}