#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_CAPACITY 3
#define BUFFER_SIZE 50

char **names;
char **numbers;

typedef struct person
{
  char *name;
  char *numbers;
  char *email;
  char *group;
} Person;

int capacity = INIT_CAPACITY; /* size of array */
int n = 0;                    /* number of people in phone directory */

char delim[] = " ";

// char command[BUFFER_SIZE];

/* function prototypes */

// functions in main.
void init_directory ();
void process_command ();

// functions for command
void load (char *fileName);
void add (char *name, char *number);
void find (char *name);
void status ();
void delete ();
void save (char *fileName);

int search (char *name);
int read_line (char str[], int limit);
void sort (char *names[]);
void reallocate ();

int
main ()
{
  init_directory ();
  process_command ();

  return 0;
}

void
init_directory ()
{
  names = (char **)malloc (INIT_CAPACITY * sizeof (char *));
  numbers = (char **)malloc (INIT_CAPACITY * sizeof (char *));
}

void
process_command ()
{
  char command_line[BUFFER_SIZE];
  char *command, *argument1, *argument2;

  while (1)
    {
      printf ("$ ");
      if (read_line (command_line, BUFFER_SIZE) <= 0)
        continue;

      command = strtok (command_line, delim);

      if (strcmp (command, "read") == 0)
        {
          argument1 = strtok (NULL, delim);
          if (argument1 == NULL)
            {
              printf ("File name required\n");
              continue;
            }
          load (argument1);
        }

      else if (strcmp (command, "add") == 0)
        {
          argument1 = strtok (NULL, delim);
          argument2 = strtok (NULL, delim);
          if (argument1 == NULL || argument2 == NULL)
            {
              printf ("Invalid arguments\n");
              continue;
            }

          add (argument1, argument2);
        }

      else if (strcmp (command, "find") == 0)
        {
          argument1 = strtok (NULL, delim);
          if (argument1 == NULL)
            {
              printf ("Invalid arguments\n");
              continue;
            }

          find (argument1);
        }

      else if (strcmp (command, "status") == 0)
        status ();

      else if (strcmp (command, "delete") == 0)
        {
          argument1 = strtok (NULL, delim);
          if (argument1 == NULL)
            {
              printf ("Invalid arguments\n");
              continue;
            }

          delete (argument1);
        }

      else if (strcmp (command, "save") == 0)
        {
          argument1 = strtok (NULL, delim);
          argument2 = strtok (NULL, delim);
          if (argument1 == NULL || strcmp (argument1, "as") != 0
              || argument2 == NULL)
            {
              printf ("Invalid command format.\n");
              continue;
            }

          save (argument2);
        }

      else if (strcmp (command, "exit") == 0)
        break;
    }
}

void
load (char *fileName)
{

  char name[BUFFER_SIZE];
  char number[BUFFER_SIZE];

  FILE *fp = fopen (fileName, "r");
  if (fp == NULL)
    {
      printf ("Open failed.\n");
      return;
    }

  while ((fscanf (fp, "%s %s", name, number)) != EOF)
    {
      add (name, number);
    }

  fclose (fp);
}

void
add (char *name, char *number)
{
  if (n >= capacity)
    reallocate ();

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
find (char *name)
{
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
    printf ("%s %s\n", *(names + i), *(numbers + i));
  printf ("Total %d persons.\n", n);
}

void delete (char *name)
{
  int index = search (name);
  if (index == -1)
    printf ("No person named %s exists.\n", name);

  int j = index;
  for (; j < n - 1; j++)
    {
      names[j] = names[j + 1];
      numbers[j] = numbers[j + 1];
    }

  n--;
  printf ("'%s' was deleted successfully.\n", name);
}

void
save (char *fileName)
{

  FILE *fp = fopen (fileName, "w");
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

int
read_line (char str[], int limit)
{
  int ch, i = 0;

  while ((ch = getchar ()) != '\n')
    if (i < limit - 1)
      str[i++] = ch;

  str[i] = '\0';

  return i;
}

void
reallocate ()
{
  capacity *= 2;
  char **new_names = (char **)malloc (capacity * sizeof (char *));
  char **new_numbers = (char **)malloc (capacity * sizeof (char *));

  for (int i = 0; i < n; i++)
    {
      new_names[i] = names[i];
      new_numbers[i] = numbers[i];
    }

  free (names);
  free (numbers);

  names = new_names;
  numbers = new_numbers;
}