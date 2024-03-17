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

Polynomial *p;
Term *t;

char fx[BUFFER_SIZE];

Polynomial *create_polynomial_instance (char name);
Term *create_term_instance ();

int read_line (char str[], int limit);
void compress_str (char str[]);
void put (char *str, Term *t);
void get_CoefAndExpo (char *coef, char *expo);

int
main ()
{
  read_line (fx, BUFFER_SIZE);
  compress_str (fx);

  p = create_polynomial_instance (fx[0]);

  char buffer[BUFFER_SIZE];
  int index = 0;

  for (int i = 2; i < strlen (fx); i++)
    {
      if (i == 2)
        {
          buffer[index++] = fx[i];
          t = create_term_instance ();
          p->first = t;
        }
      else
        {
          if ((fx[i] == '+' || fx[i] == '-'))
            {
              buffer[index] = '\0';
              put (buffer, t);
              t->next = create_term_instance ();
              t = t->next;

              index = 0;
              buffer[index++] = fx[i];
            }

          else
            {
              buffer[index++] = fx[i];
            }
        }
    }

  buffer[index] = '\0';
  put (buffer, t);
  t->next = NULL;

  Term *ptr = p->first;

  while (ptr != NULL)
    {
      printf ("%d \n", ptr->coef);
      ptr = ptr->next;
    }

  return 0;
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

void
compress_str (char str[])
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
}

void
put (char *str)
{
  char coef[BUFFER_SIZE];
  char expo[BUFFER_SIZE];

  get_CoefAndExpo (str, coef, expo);

  if (strcmp (coef, "\0") == 0 || strcmp (coef, "+") == 0)
    {
      coef[0] = '1';
      coef[1] = '\0';
    }

  if (strcmp (coef, "-") == 0)
    {
      coef[0] = '-';
      coef[1] = '1';
      coef[2] = '\0';
    }

  if (strcmp (expo, "\0") == 0)
    {
      expo[0] = '1';
      expo[1] = '\0';
    }

  t->coef = atoi (coef);
  t->expo = atoi (expo);
}

void
get_CoefAndExpo (char *str, char *coef, char *expo)
{
  int flag = 0, c = 0, e = 0;
  for (int i = 0; i < strlen (str); i++)
    {
      if (str[i] == 'x' || str[i] == '^')
        {
          flag = 1;
          continue;
        }

      if (flag == 0)
        {
          coef[c++] = str[i];
        }

      else if (flag == 1)
        {
          expo[e++] = str[i];
        }
    }

  coef[c] = '\0';
  expo[e] = '\0';
}