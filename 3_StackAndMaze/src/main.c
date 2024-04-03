#define _CRT_SECURE_NO_WARNINGS

#include "pos.h"
#include "stack.h"
#include <stdio.h>

#define MAX 100
#define PATH 0        // ������ �� �ִ� ��ġ
#define WALL 1        // ������ �� ���� ��ġ
#define VISITED 2     // �̹� �湮�� ��ġ
#define BACKTRACKED 3 // �湮�ߴٰ� �ǵ��� ���� ��ġ

int maze[MAX][MAX];
int n; //�̷��� ���� ũ��+
int m; //�̷��� ���� ũ��

int read_maze();
void print_maze();
bool movable(Position pos, int dir);

int main()
{
    read_maze();
    print_maze();
    Stack s = create();
    Position cur; //���� ��ġ�� ǥ��
    cur.x = 0;
    cur.y = 0;

    int init_dir = 0; // � ��ġ�� �������� �� ó������ �õ��� �� �̵� ����

    while (1)
    {
        maze[cur.x][cur.y] = VISITED;         // ���� ��ġ �湮�ߴٰ�
        if (cur.x == n - 1 && cur.y == m - 1) // ���� ��ġ�� �ⱸ���.
        {
            printf("Found the path.\n");
            break;
        }

        bool forwarded = false; // 4���� �� �� ������ �����ϴµ� �����ߴ��� ǥ��
        for (int dir = init_dir; dir < 4; dir++)
        {
            if (movable(cur, dir))
            {
                push(s, dir);
                cur = move_to(cur, dir);
                forwarded = true;
                init_dir = 0;
                break;
            }
        }

        if (!forwarded)
        {
            maze[cur.x][cur.y] = BACKTRACKED;
            if (is_empty(s))
            {
                printf("No path exists.\n");
                break;
            }
            int d = pop(s);
            cur = move_to(cur, (d + 2) % 4); //�ݴ� �������� ����
            init_dir = d + 1;
        }

        print_maze();
    }

    print_maze();
    return 0;
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
                printf("%d", maze[i][j]);
        }
        printf("\n");
    }
    printf("\n");
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