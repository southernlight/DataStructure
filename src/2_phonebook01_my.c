#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 10
#define INIT_CAPACITY 3
#define BUFFER_SIZE 50

char **names;   /* names */
char **numbers; /* phone numbers */

int capacity = INIT_CAPACITY;
int n = 0; /* number of people in phone directory */
char delim[] = " ";
char *token;
char command[BUFFER_SIZE];

void init_directory ();
void process_command ();

void load ();
void add ();
void find ();
void status ();
void delete ();
void save ();
void sort (char *names[]);
int search (char *name);
int read_line (char str[], int limit);

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
  names = (char **)malloc (capacity * sizeof (char *));
  numbers = (char **)malloc (capacity * sizeof (char *));
}

void
process_command ()
{
  while (1)
    {
      printf ("$ ");
      read_line (command, BUFFER_SIZE);

      token = strtok (command, delim);

      if (strcmp (token, "read") == 0)
        load ();
      else if (strcmp (token, "add") == 0)
        add ();
      else if (strcmp (token, "find") == 0)
        find ();
      else if (strcmp (token, "status") == 0)
        status ();
      else if (strcmp (token, "delete") == 0)
        delete ();
      else if (strcmp (token, "save") == 0)
        save ();
      else if (strcmp (token, "exit") == 0)
        break;
    }
}

void
load ()
{
  int count = 0;

  char file_name[BUFFER_SIZE], name[BUFFER_SIZE], number[BUFFER_SIZE];

  while ((token = strtok (NULL, delim)) != NULL)
    {
      count++;
      if (count == 1)
        strcpy (file_name, token);
    }

  if (count < 1)
    printf ("File name required\n");

  else if (count == 1)
    {
      FILE *fp = fopen (file_name, "r");
      if (fp == NULL)
        {
          printf ("Open failed.\n");
          return;
        }

      while ((fscanf (fp, "%s %s", name, number)) != EOF)
        {
          n++;
        }

      // sort(names);

      names = (char **)malloc (n * sizeof (char *));
      numbers = (char **)malloc (n * sizeof (char *));

      for (int i = 0; i < n; ++i)
        {
          *(names + i) = _strdup (name);
          *(numbers + i) = _strdup (number);
        }

      fclose (fp);
    }

  else
    printf ("Too many arguments\n");
}

void
add ()
{
  int count = 0;

  char name[BUFFER_SIZE], number[BUFFER_SIZE];

  // scanf("%s %s", name, number);
  while ((token = strtok (NULL, delim)) != NULL)
    {
      count++;
      if (count == 1)
        strcpy (name, token);
      else if (count == 2)
        strcpy (number, token);
    }

  if (count == 2)
    {
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

  else
    printf ("Invalid arguments\n");
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
    printf ("%s %s\n", *(names + i), *(numbers + i));
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
      // printf("%d\n", j);
    }

  n--;
  printf ("'%s' was deleted successfully.\n", name);
}

void
save ()
{
  int count = 0;

  char file_name[BUFFER_SIZE];
  char tmp[BUFFER_SIZE];

  // scanf("%s", tmp);
  // scanf("%s", file_name);

  while ((token = strtok (NULL, delim)) != NULL)
    {
      count++;
      if (count == 1)
        strcpy (tmp, token);
      else if (count == 2)
        strcpy (file_name, token);
    }

  if (count == 2 && (strcmp (tmp, "as") == 0))
    {
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

  else
    printf ("Invalid command format.\n");
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