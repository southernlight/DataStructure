#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 100

int read_line (char str[], int n);
int compress_with_additional_array (char str[]);

int
main (void)
{
  char buffer[BUFFER_SIZE];
  int k;

  while (1)
    {
      printf ("$ ");
      k = read_line (buffer, BUFFER_SIZE);
      compress_with_additional_array (buffer);
      printf ("%s:%d\n", buffer, strlen (buffer));
    }

  return 0;
}

int
read_line (char str[], int limit)
{
  int ch, i = 0;

  while ((ch = getchar ()) != '\n')
    {
      if (i < limit - 1)
        str[i++] = ch;
    }

  str[i] = '\0';

  return i;
}

int
compress_with_additional_array (char str[])
{
  int j = 0;

  for (int i = 0; i < strlen (str) + 1; ++i)
    {
      if (str[i] == ' ')
        {
          if (i == 0)
            ;
          else if (str[i - 1] != ' ')
            {
              str[j] = str[i];
              j++;
            }
        }

      else if (str[i] == '\0')
        {
          if (str[j] == ' ')
            str[j - 1] = '\0';
        }

      else
        {
          str[j] = str[i];
          j++;
        }
    }

  return 0;
}
