#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 20

int read_line (char str[], int n);

int
main (void)
{
  char buffer[BUFFER_SIZE];
  int k;

  while (1)
    {
      printf ("$ ");
      k = read_line (buffer, BUFFER_SIZE);
      printf ("%s:%d\n", buffer, strlen (buffer));
    }

  return 0;
}

int
read_line (char str[], int n)
{
  int ch, i = 0;

  while ((ch = getchar ()) != '\n')
    {
      if (i < n)
        str[i++] = ch;
    }

  return i;
}
