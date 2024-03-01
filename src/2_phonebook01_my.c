#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 100

char command[CAPACITY];
char *names[CAPACITY];
char *numbers[CAPACITY];
int index;

void add (void);
void find (void);
void status (void);
void delete (void);

int
main ()
{

  while (1)
    {
      printf ("$ ");
      scanf ("%s", command);

      if (!(strcmp ("add", command)))
        add ();
      else if (!(strcmp ("find", command)))
        find ();
      else if (!(strcmp ("status", command)))
        status ();
      else if (!(strcmp ("delete", command)))
        delete ();
      else if (!(strcmp ("exit", command)))
        break;
      else if (!(strcmp ("clear", command)))
        system ("cls");
      else
        {
          printf ("%s is not a command\n", command);
          printf ("Choose one of those-> add, find, status, delete, exit, "
                  "clear\n");
          while (getchar () != '\n')
            continue;
        }
    }

  return 0;
}

void
add (void)
{
  char name[CAPACITY];
  char number[CAPACITY];

  scanf ("%s %s", name, number);

  names[index] = _strdup (name);
  numbers[index] = _strdup (number);

  index++;

  printf ("%s was added successfully\n", name);

  while (getchar () != '\n')
    continue;
}

void
find (void)
{
  char name[CAPACITY];
  bool find = false;

  scanf ("%s", name);

  for (int i = 0; i < index; i++)
    {
      if (!(strcmp (names[i], name)))
        {
          printf ("%s\n", numbers[i]);
          find = true;
          break;
        }
    }

  if (find == false)
    printf ("No person named '%s' exists\n", name);

  while (getchar () != '\n')
    continue;
}

void
status (void)
{
  for (int i = 0; i < index; i++)
    {
      printf ("%s %s\n", names[i], numbers[i]);
    }

  printf ("Total %d persons.\n", index);
}

void delete (void)
{
  char name[CAPACITY];
  bool find = false;

  scanf ("%s", name);

  for (int i = 0; i < index; i++)
    {
      if (!(strcmp (names[i], name)))
        {
          names[i] = NULL;
          numbers[i] = NULL;
          index--;

          for (int j = i; j < index; j++)
            {
              names[j] = names[j + 1];
              numbers[j] = numbers[j + 1];
            }

          find = true;
          printf ("%s was deleted successfully.\n", name);
          break;
        }
    }
  if (find == false)
    printf ("No person named '%s' exists\n", name);
}
