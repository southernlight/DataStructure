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

void load ();
void add ();
void find ();
void status ();
void delete ();
void save ();
void sort (char *names[]);
int search (char *name);

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
    }

  return 0;
}

void
load ()
{
  char file_name[BUFFER_SIZE], name[BUFFER_SIZE], number[BUFFER_SIZE];
  scanf ("%s", file_name);

  FILE *fp = fopen (file_name, "r");
  if (fp == NULL)
    {
      printf ("Open failed.\n");
      return;
    }

  while ((fscanf (fp, "%s %s", name, number)) != EOF)
    {
      names[n] = _strdup (name);
      numbers[n] = _strdup (number);
      n++;
    }

  sort (names);

  fclose (fp);
}

void
add ()
{
  char name[BUFFER_SIZE], number[BUFFER_SIZE];

  scanf ("%s %s", name, number);

  int i = n - 1;
  while (i >= 0 && strcmp (names[i], name) > 0)
    {
      names[i + 1] = names[i];
      numbers[i + 1] = numbers[i];
      i--;
    }

  names[i + 1] = _strdup (name);
  numbers[i + 1] = _strdup (number);

  n++;
  printf ("%s was added successfully\n", name);
}

void
find ()
{
  char name[BUFFER_SIZE];
  scanf ("%s", name);

  int index = search (name);

  if (index == -1)
    printf ("No person named '%s' exists\n", name);
  else
    printf ("%s\n", numbers[index]);
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
  int index = search (name);
  if (index == -1)
    printf ("No person named %s exists.\n", name);

  int j = index;
  for (; j < n - 1; j++)
    {
      names[j] = names[j + 1];
      numbers[j] = numbers[j + 1];
      printf ("%d\n", j);
    }

  n--;
  printf ("'%s' was deleted successfully.\n", name);
}

void
save ()
{
  char file_name[BUFFER_SIZE];
  char tmp[BUFFER_SIZE];

  scanf ("%s", tmp);
  scanf ("%s", file_name);

  FILE *fp = fopen (file_name, "w");
  if (fp == NULL)
    {
      printf ("Open failed");
      return;
    }

  for (int i = 0; i < n; i++)
    {
      fprintf (fp, "%s ", names[i]);
      fprintf (fp, "%s\n", numbers[i]);
    }

  fclose (fp);
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

int
search (char *name)
{
  for (int i = 0; i < n; i++)
    {
      if (strcmp (name, names[i]) == 0)
        return i;
    }

  return -1;
}