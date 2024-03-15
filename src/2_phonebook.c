#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LENGTH 100
#define INIT_CAPACITY 2

typedef struct person
{
  char *name;
  char *number;
  char *email;
  char *group;
} Person;

Person **directory;

int capacity = 0;
int n;

/* function prototypes */

// functions in main.
void init ();
void process_command ();
// functions for command
void load (char *fileName);
void handle_add (char *name);
void find (char *name);
void status ();
void delete ();
void save (char *fileName);

int search (char *name);
int read_line (FILE *fp, char str[], int limit);
int compose_name (char *name_str, int limit);
void print_person (Person *person);
void add (char *name, char *number, char *email, char *group);
void reallocate ();
void release_person (Person *p);

int
main ()
{
  init ();
  process_command ();

  return 0;
}

void
init ()
{
  directory = (Person **)malloc (INIT_CAPACITY * sizeof (Person *));
  capacity = INIT_CAPACITY;
  n = 0;
}

void
process_command ()
{
  char command_line[BUFFER_LENGTH];
  char *command, *argument;
  char name_str[BUFFER_LENGTH];

  while (1)
    {
      printf ("$ ");
      if (read_line (stdin, command_line, BUFFER_LENGTH) <= 0)
        continue;

      command = strtok (command_line, " ");

      if (strcmp (command, "read") == 0)
        {
          argument = strtok (NULL, " ");
          if (argument == NULL)
            {
              printf ("File name required\n");
              continue;
            }
          load (argument);
        }

      else if (strcmp (command, "add") == 0)
        {

          if (compose_name (name_str, BUFFER_LENGTH) == 0)
            printf ("Invalid arguments\n");
          else
            handle_add (name_str);
        }

      else if (strcmp (command, "find") == 0)
        {
          if (compose_name (name_str, BUFFER_LENGTH) == 0)
            printf ("Invalid arguments\n");
          else
            find (name_str);
        }

      else if (strcmp (command, "status") == 0)
        status ();

      else if (strcmp (command, "delete") == 0)
        {
          if (compose_name (name_str, BUFFER_LENGTH) == 0)
            printf ("Invalid arguments\n");
          else
            {
              delete (name_str);
            }
        }

      else if (strcmp (command, "save") == 0)
        {
          argument = strtok (NULL, " ");
          if (argument == NULL || strcmp (argument, "as") != 0)
            {
              printf ("Invalid command format.\n");
              continue;
            }

          argument = strtok (NULL, " ");
          save (argument);
        }

      else if (strcmp (command, "exit") == 0)
        break;
    }
}

void
load (char *fileName)
{
  char buffer[BUFFER_LENGTH];
  char *name, *number, *email, *group;
  char *token;

  FILE *fp = fopen (fileName, "r");
  if (fp == NULL)
    {
      printf ("Open failed.\n");
      return;
    }

  while ((read_line (fp, buffer, BUFFER_LENGTH) > 0))
    {
      name = strtok (buffer, "#");
      token = strtok (NULL, "#");
      if (strcmp (token, " ") == 0)
        number = NULL;
      else
        number = _strdup (token);

      token = strtok (NULL, "#");
      if (strcmp (token, " ") == 0)
        email = NULL;
      else
        email = _strdup (token);

      token = strtok (NULL, "#");
      if (strcmp (token, " ") == 0)
        group = NULL;
      else
        group = _strdup (token);

      add (_strdup (name), number, email, group);
    }

  fclose (fp);
}

void
handle_add (char *name)
{
  char number[BUFFER_LENGTH], email[BUFFER_LENGTH], group[BUFFER_LENGTH];

  printf ("  Phone: ");
  read_line (stdin, number, BUFFER_LENGTH);
  printf ("  Email: ");
  read_line (stdin, email, BUFFER_LENGTH);
  printf ("  Group: ");
  read_line (stdin, group, BUFFER_LENGTH);

  add (_strdup (name), (char *)(strlen (number) > 0 ? _strdup (number) : NULL),
       (char *)(strlen (email) > 0 ? _strdup (email) : NULL),
       (char *)(strlen (group) > 0 ? _strdup (group) : NULL));

  printf ("%s was added successfully.\n", name);
}

void
find (char *name)
{
  int index = search (name);

  if (index == -1)
    printf ("No person named '%s' exists\n", name);
  else
    {
      printf ("%s:\n", directory[index]->name);
      printf ("  Phone: %s\n", directory[index]->number);
      printf ("  Email: %s\n", directory[index]->email);
      printf ("  Group: %s\n", directory[index]->group);
    }
}

void
status ()
{
  for (int i = 0; i < n; i++)
    print_person (directory[i]);
  printf ("Total %d persons.\n", n);
}

void delete (char *name)
{
  int index = search (name);
  if (index == -1)
    printf ("No person named %s exists.\n", name);

  Person *p = directory[index];
  for (int j = index; j < n - 1; j++)
    directory[j] = directory[j + 1];
  n--;
  release_person (p);
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
      fprintf (fp, "%s", directory[i]->name);
      fprintf (fp, "#");

      if (directory[i]->number == NULL)
        fprintf (fp, " ");
      else
        fprintf (fp, "%s", directory[i]->number);
      fprintf (fp, "#");

      if (directory[i]->email == NULL)
        fprintf (fp, " ");
      else
        fprintf (fp, "%s", directory[i]->email);
      fprintf (fp, "#");

      if (directory[i]->group == NULL)
        fprintf (fp, " ");
      else
        fprintf (fp, "%s", directory[i]->group);
      fprintf (fp, "#");

      fprintf (fp, "\n");
    }

  fclose (fp);
}

int
search (char *name)
{
  for (int i = 0; i < n; i++)
    {
      if (strcmp (name, directory[i]->name) == 0)
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

      ptr = strtok (NULL, " ");
    }

  name_str[length - 1] = '\0';

  return length;
}

void
print_person (Person *p)
{
  printf ("%s:\n", p->name);
  printf ("  Phone: %s\n", p->number);
  printf ("  Email: %s\n", p->email);
  printf ("  Group: %s\n", p->group);
  printf ("\n");
}

void
add (char *name, char *number, char *email, char *group)
{
  if (n >= capacity)
    reallocate ();

  int i = n - 1;
  while (i >= 0 && strcmp (directory[i]->name, name) > 0)
    {
      directory[i + 1] = directory[i];
      i--;
    }
  directory[i + 1] = (Person *)malloc (sizeof (Person));

  directory[i + 1]->name = name;
  directory[i + 1]->number = number;
  directory[i + 1]->email = email;
  directory[i + 1]->group = group;

  n++;
}

void
reallocate ()
{
  capacity *= 2;
  Person **tmp = (Person **)malloc (capacity * sizeof (Person *));
  for (int i = 0; i < n; i++)
    {
      tmp[i] = directory[i];
    }
  free (directory);
  directory = tmp;
}

void
release_person (Person *p)
{
  free (p->name);
  if (p->number != NULL)
    free (p->number);
  if (p->email != NULL)
    free (p->email);
  if (p->group != NULL)
    free (p->group);
  free (p);
}