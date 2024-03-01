#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 100
#define BUFFER_SIZE 20

char *names[CAPACITY];   /* names */
char *numbers[CAPACITY]; /* phone numbers */
int n = 0;               /* number of people in phone directory */

void add ();
void find ();
void status ();
void delete ();

int
main ()
{
  char command[BUFFER_SIZE];
  while (1)
    {
      printf ("$ ");
      scanf ("%s", command);

      if (strcmp (command, "add") == 0)
        add ();
      else if (strcmp (command, "find") == 0)
        find ();
      else if (strcmp (command, "status") == 0)
        status ();
      else if (strcmp (command, "delete") == 0)
        delete ();
      else if (strcmp (command, "exit") == 0)
        break;
    }

  return 0;
}

void
add ()
{
  char name[BUFFER_SIZE], number[BUFFER_SIZE];
  scanf ("%s %s", name, number);

  names[n] = _strdup (name);
  numbers[n] = _strdup (number);
  n++;

  printf ("%s was added successfully\n", name);
}

void
find ()
{
  char name[BUFFER_SIZE];
  scanf ("%s", name);

  for (int i = 0; i < n; i++)
    {
      if (strcmp (names[i], name) == 0)
        {
          printf ("%s\n", numbers[i]);
          return;
        }
    }

  printf ("No person named '%s' exists\n", name);
}

void
status ()
{
  for (int i = 0; i < n; i++)
    printf ("%s %s\n", names[i], numbers[i]);
  printf ("Total %d persons.\n", n);
}

void delete ()
{
  char name[BUFFER_SIZE];
  scanf ("%s", name);

  for (int i = 0; i < n; i++)
    {
      if (strcmp (name, names[i]) == 0)
        {
          names[i] = names[n - 1];
          numbers[i] = names[n - 1];
          n--;
          printf ("'%s' was deleted successfully.\n", name);
          return;
        }
    }
  printf ("No person named '%s' exists.\n", name);
}
