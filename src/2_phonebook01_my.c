#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_CAPACITY 3
#define CAPACITY 100
#define BUFFER_LENGTH 100
#define BUFFER_SIZE 50

char **names;
char **numbers;

typedef struct person
{
  char *name;
  char *number;
  char *email;
  char *group;
} Person;

int capacity = INIT_CAPACITY; /* size of array */
Person directory[CAPACITY];

int n = 0; /* number of people in phone directory */
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
int read_line (FILE *fp, char str[], int limit);
void sort (char *names[]);
void reallocate ();
int compose_name (char *name_str, int limit);
void handle_add (name_str);

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
  char *command, *argument;
  char name_str[BUFFER_LENGTH]; // 사람이름

  while (1)
    {
      printf ("$ ");
      if (read_line (stdin, command_line, BUFFER_SIZE) <= 0)
        continue;

      command = strtok (command_line, delim);

      if (strcmp (command, "read") == 0)
        {
          argument = strtok (NULL, delim);
          if (argument == NULL)
            {
              printf ("File name required\n");
              continue;
            }
          load (argument);
        }

      else if (strcmp (command, "add") == 0)
        {
          // int k=compose_name(name_str, BUFFER_LENGTH);
          // printf("%s %d\n", name_str, k);

          if (compose_name (name_str, BUFFER_LENGTH) == 0)
            printf ("Invalid arguments\n");
          else
            handle_add (name_str);

          fgetc (stdin);
        }

      else if (strcmp (command, "find") == 0)
        {
          argument = strtok (NULL, delim);
          if (argument == NULL)
            {
              printf ("Invalid arguments\n");
              continue;
            }

          find (argument);
        }

      else if (strcmp (command, "status") == 0)
        status ();

      else if (strcmp (command, "delete") == 0)
        {
          argument = strtok (NULL, delim);
          if (argument == NULL)
            {
              printf ("Invalid arguments\n");
              continue;
            }

          delete (argument);
        }

      else if (strcmp (command, "save") == 0)
        {
          argument = strtok (NULL, delim); // as
          if (argument == NULL || strcmp (argument, "as") != 0)
            {
              printf ("Invalid command format.\n");
              continue;
            }

          save (name_str);
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
read_line (FILE *fp, char str[], int limit)
{
  int ch, i = 0;
  while ((ch = fgetc (fp)) != '\n' && ch != EOF)
    if (i < limit - 1)
      {
        str[i++] = ch;
      }
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

int
compose_name (char *name_str, int limit)
{
  char *ptr;
  int length = 0;

  ptr = strtok (NULL, " ");
  if (ptr == NULL)
    return 0;

  while (ptr != NULL)
    {

      for (int i = 0; i <= strlen (ptr); i++)
        {
          if (ptr[i] == '\0')
            name_str[length + i] = ' ';
          else
            name_str[length + i] = ptr[i];
        }
      length += strlen (ptr) + 1;

      ptr = strtok (NULL, delim);
    }

  name_str[length - 1] = '\0';

  return length;
}

void
handle_add (char *name_str)
{
  char number_buf[100], email_buf[100], group_buf[100];
  Person registrant = { " ", " ", " ", " " };

  printf ("Phone: ");
  scanf ("%s", number_buf);
  printf ("Email: ");
  scanf ("%s", email_buf);
  printf ("Group: ");
  scanf ("%s", group_buf);

  registrant.name = _strdup (name_str);
  registrant.number = _strdup (number_buf);
  registrant.email = _strdup (email_buf);
  registrant.group = _strdup (group_buf);

  // printf("%s %s %s %s\n", registrant.name, registrant.number,
  // registrant.email, registrant.group);

  directory[n] = registrant;
  n++;

  printf ("%s was added successfully.\n", name_str);
}