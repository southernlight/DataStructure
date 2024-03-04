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
FILE *fr;
FILE *fw;

void load ();
void add ();
void find ();
void status ();
void delete ();
void save ();
void sort (char *names[]);

int
main ()
{
  char command[BUFFER_SIZE];
  while (1)
    {
      printf ("$ ");
      scanf ("%s", command);
      if (strcmp (command, "read") == 0)
        load ();
      else if (strcmp (command, "add") == 0)
        add ();
      else if (strcmp (command, "find") == 0)
        find ();
      else if (strcmp (command, "status") == 0)
        status ();
      else if (strcmp (command, "delete") == 0)
        delete ();
      else if (strcmp (command, "save") == 0)
        save ();
      else if (strcmp (command, "exit") == 0)
        break;

      sort (names);
    }

  return 0;
}

void
load ()
{
  char file_name[BUFFER_SIZE], name[BUFFER_SIZE], number[BUFFER_SIZE];
  scanf ("%s", file_name);

  fr = fopen (file_name, "r");

  while ((fscanf (fr, "%s %s", name, number)) != EOF)
    {
      names[n] = _strdup (name);
      numbers[n] = _strdup (number);
      n++;
    }

  fclose (fr);
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
          numbers[i] = numbers[n - 1];
          n--;
          printf ("'%s' was deleted successfully.\n", name);
          return;
        }
    }
  printf ("No person named '%s' exists.\n", name);
}

void
save ()
{
  char file_name[BUFFER_SIZE];
  scanf ("%s", file_name);
  fw = fopen (file_name, "w");
  if (fw == NULL)
    {
      printf ("Open failed");
    }

  for (int i = 0; i < n; i++)
    {
      fprintf (fw, "%s ", names[i]);
      fprintf (fw, "%s\n", numbers[i]);
    }

  fclose (fw);
}

void
sort (char *names[])
{
  int min;
  int length = 0;
  char *temp;

  while (names[length] != '\0')
    length++;

  for (int i = 0; i < length; i++)
    {
      min = i;
      for (int j = i + 1; j < length; j++)
        {

          for (int k = 0; k < strlen (names[j]); k++)
            {
              if (names[j][k] < names[min][k])
                {
                  min = j;
                  break;
                }

              else if (names[j][k] > names[min][k])
                break;
              else
                continue;
            }
        }

      temp = names[min];
      names[min] = names[i];
      names[i] = temp;
    }
}