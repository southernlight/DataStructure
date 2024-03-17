#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100

typedef struct term
{
  int coef;
  int expo;
  struct term *next;
} Term;

typedef struct polynomial
{
  char name;
  Term *first;
  int size;

} Polynomial;

Polynomial *polys[BUFFER_SIZE];
int n = 0;

void process_command ();
void handle_calc (char poly_name, char *input_value);
void handle_print (char poly_name);
void handle_definition (char *poly);

Polynomial *create_polynomial_instance (char name);
Term *create_term_instance ();
int read_line (char *str, int limit);
int compress (char *str);
void add_term (int c, int e, Polynomial *poly);

int
main ()
{
  process_command ();

  return 0;
}

void
process_command ()
{
  char command_line[BUFFER_SIZE];
  char *command, *arg1, *arg2;
  char copied[BUFFER_SIZE];

  while (1)
    {
      printf ("$ ");
      if (read_line (command_line, BUFFER_SIZE) <= 0)
        continue;
      strcpy (copied, command_line);
      command = strtok (command_line, " ");

      if (strcmp (command, "calc") == 0)
        {
          arg1 = strtok (NULL, " ");
          arg2 = strtok (NULL, " ");

          if (arg1 == NULL || arg2 == NULL)
            {
              printf ("Invalid arguments.\n");
              continue;
            }
          handle_calc (arg1[0], arg2);
        }

      else if (strcmp (command, "print") == 0)
        {
          arg1 = strtok (NULL, " ");
          if (arg1 == NULL)
            {
              printf ("Invalid arguments.\n");
              continue;
            }
          handle_print (arg1[0]);
        }

      else if (strcmp (command, "exit") == 0)
        break;

      else
        {
          handle_definition (copied);
        }
    }
}

void
handle_calc (char poly_name, char *input_value)
{
  ;
}
void
handle_print (char poly_name)
{
  ;
}
void
handle_definition (char *poly)
{
  int length;
  length = compress (poly);
  polys[n++] = create_polynomial_instance (poly[0]);
}

Polynomial *
create_polynomial_instance (char name)
{
  Polynomial *ptr_poly = (Polynomial *)malloc (sizeof (Polynomial));
  ptr_poly->name = name;
  ptr_poly->first = NULL;
  ptr_poly->size = 0;

  return ptr_poly;
}

Term *
create_term_instance ()
{

  Term *t = (Term *)malloc (sizeof (Term));
  t->coef = 0;
  t->expo = 0;

  return t;
}

int
read_line (char *str, int limit)
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
compress (char *str)
{
  int n = 0;
  for (int i = 0; i < strlen (str); i++)
    {
      if (str[i] != ' ')
        {
          str[n++] = str[i];
        }
    }
  str[n] = '\0';

  return n;
}

void
add_term (int c, int e, Polynomial *poly)
{
  ;
}

Term *
find (Polynomial *poly, int e)
{
  Term *t = poly->first;

  while (t != NULL)
    {
      if (t->expo <= e)
        return t;
      t = t->next;
    }

  return NULL;
}

int
add_after (Term *prev, int c, int e)
{
  ;
}