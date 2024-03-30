#define _CRT_SECURE_NO_WARNINGS

#include "pos.h"
#include "stack.h"
#include <stdio.h>

#define MAX 100
#define PATH 0        // 지나갈 수 있는 위치
#define WALL 1        // 지나갈 수 없는 위치
#define VISITED 2     // 이미 방문한 위치
#define BACKTRACKED 3 // 방문했다가 되돌아 나온 위치

int maze[MAX][MAX];
int n; // 미로의 가로 크기
int m; // 미로의 세로 크기

int read_maze ();
void print_maze ();
bool movable (Position pos, int dir);

int
main ()
{
  read_maze ();
  print_maze ();
  Stack s = create ();
  Position cur; // 현재 위치를 표현
  cur.x = 0;
  cur.y = 0;

  int init_dir = 0; // 어떤 위치에 도착했을 때 처음으로 시도해 볼 이동 방향

  while (1)
    {
      maze[cur.x][cur.y] = VISITED;         // 현재 위치 방문했다고
      if (cur.x == n - 1 && cur.y == m - 1) // 현재 위치가 출구라면.
        {
          printf ("Found the path.\n");
          break;
        }

      bool forwarded = false; // 4방향 중 한 곳으로 전진하는데 성공했는지 표시
      for (int dir = init_dir; dir < 4; dir++)
        {
          if (movable (cur, dir))
            {
              push (s, dir);
              cur = move_to (cur, dir);
              forwarded = true;
              init_dir = 0;
              break;
            }
        }

      if (!forwarded)
        {
          maze[cur.x][cur.y] = BACKTRACKED;
          if (is_empty (s))
            {
              printf ("No path exists.\n");
              break;
            }
          int d = pop (s);
          cur = move_to (cur, (d + 2) % 4); // 반대 방향으로 가기
          init_dir = d + 1;
        }

      print_maze ();
    }

  print_maze ();
  return 0;
}

int
read_maze ()
{
  char ch;
  int row = 0, col = 0;

  FILE *fp = fopen ("maze.txt", "r");
  if (fp == NULL)
    return 0;
  fscanf (fp, "%d %d", &n, &m);

  while (fgetc (fp) != '\n')
    continue;

  while ((ch = fgetc (fp)) != EOF)
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

void
print_maze ()
{
  for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
        {
          if (maze[i][j] == 2)
            printf ("*");
          else
            printf ("%d", maze[i][j]);
        }
      printf ("\n");
    }
  printf ("\n");
}

bool //movable 이면 trur movable 하지 않으면 false
movable (Position pos, int dir)
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
