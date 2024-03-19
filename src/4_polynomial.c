#define _CRT_SECURE_NO_WARNINGS

#include <math.h>
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

Polynomial *create_by_parse_polynomial (char name, char *body);
int parse_and_add_term (char *expr, int begin, int end, Polynomial *ptr_poly);

Polynomial *create_polynomial_instance (char name);
Term *create_term_instance ();
int read_line (char *str, int limit);
void compress (char *str);

void add_term (int c, int e, Polynomial *poly);
Term *remove_first (Polynomial *poly);
Term *remove_after (Term *prev);
void add_first (int c, int e, Polynomial *poly);
void add_after (int c, int e, Term *prev);
int eval_poly (Polynomial *poly, int x);
int eval_term (Term *, int x);
void print_poly (Polynomial *p);
void print_term (Term *pTerm, Polynomial *poly);
Polynomial *findPolyByName (char poly_name);
void insert_polynomial (Polynomial *ptr_poly);
void destroy_polynomial (Polynomial *ptr_poly);

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
  Polynomial *p = findPolyByName (poly_name);
  eval_poly (p, atoi (input_value));
}
void
handle_print (char poly_name)
{
  Polynomial *p = findPolyByName (poly_name);
  print_poly (p);
}
void
handle_definition (char *expression)
{
  char name;
  char *body;
  Polynomial *p;

  compress (expression);
  name = (strtok (expression, "="))[0];
  body = strtok (NULL, "");

  p = create_by_parse_polynomial (name, body);
  polys[n] = p;
  n++;
}

Polynomial *
create_by_parse_polynomial (char name, char *body)
{
  Polynomial *ptr_poly = create_polynomial_instance (name);
  int i = 0, begin_term = 0,
      result
      = 0; // begin_term은 -,+를 만날 때 그 자리로 인덱스 숫자가 변경된다.
  while (i < strlen (body))
    {
      if (body[i] == '+' || body[i] == '-' || i == 0)
        begin_term = i;
      i++;
      if (body[i] == '+' || body[i] == '-')
        result = parse_and_add_term (body, begin_term, i, ptr_poly);
    }

  return ptr_poly;
}

int
parse_and_add_term (char *expr, int begin, int end, Polynomial *p_poly)
{
  int i = begin;
  int c_index = 0, e_index = 0;
  int sign_coef = 1;      //-1: 음수 1: 양수
  int coef = 0, expo = 1; // coef 는 계수의 절댓값

  char buffer_coef[BUFFER_SIZE];
  char buffer_expo[BUFFER_SIZE];

  if (expr[begin] == '+' || (expr[begin] >= '1' && expr[begin] <= '9'))
    sign_coef = 1; // 양수
  else if (expr[begin] == '-')
    sign_coef = -1; // 음수

  while ((i < end)
         && ((expr[i] >= '0' && expr[i] <= '9')
             || (expr[i] == '+' || expr[i] == '-')))
    {
      buffer_coef[c_index++] = expr[i];
      i++;
    }
  buffer_coef[c_index] = '\0';

  coef = sign_coef * abs (atoi (buffer_coef));

  if (coef == 0) // coef 가 0인 경우->계수가 1또는 -1인 x -x를 나타낸다.
    coef = 1;

  if (i == end) // 문자를 다 읽은 경우->상수항
    {
      add_term (coef, expo, p_poly);
      return 1;
    }

  if (expr[i] != 'x')
    return 0;
  i++;

  if (i == end)
    {
      add_term (coef, expo, p_poly);
      return 1;
    }

  if (expr[i] != '^')
    return 0;
  i++;

  for (i; i < end; i++)
    {
      if (!(expr[i] > '0' && expr[i] < '9'))
        return 0;
      buffer_expo[e_index++] = expr[i];
    }

  buffer_expo[e_index] = '\0';
  expo = atoi (buffer_expo);

  add_term (coef, expo, p_poly);
  return 1;
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

void
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
}

void
add_term (int c, int e, Polynomial *poly)
{
  if (c == 0)
    return;
  Term *p = poly->first;
  Term *q = NULL;

  while (p != NULL && p->expo > e)
    {
      q = p;
      p = p->next;
    }

  if (p != NULL && p->expo == e)
    {
      p->coef += c;
      if (p->coef == 0)
        {
          if (q == NULL) // 처음 것 지우기
            poly->first = p->next;
          else // q 다음 것 지우기
            q->next = p->next;

          poly->size--;
          free (p);
        }

      return;
    }

  Term *t = create_term_instance ();
  t->coef = c;
  t->expo = e;

  if (q == NULL) // 맨앞에 삽입해야하는 경우
    add_first (c, e, poly);
  else // q의 뒤, p의 앞에 삽입해야하는 경우
    add_after (c, e, q);
  poly->size++;
}

void
add_first (int c, int e, Polynomial *poly)
{
  Term *t = create_term_instance ();
  t->coef = c;
  t->expo = e;

  t->next = poly->first;
  poly->first = t;
}

void
add_after (int c, int e, Term *prev)
{
  Term *t = create_term_instance ();
  t->coef = c;
  t->expo = e;

  t->next = prev->next;
  prev->next = t;
}

int
eval_poly (Polynomial *poly, int x)
{
  int value = 0;
  Term *t = poly->first;

  while (t != NULL)
    {
      value += eval_term (t, x);
      t = t->next;
    }

  return value;
}

int
eval_term (Term *t, int x)
{
  return (int)((t->coef) * pow ((double)x, (double)(t->expo)));
}

void
print_poly (Polynomial *poly)
{
  Term *t = poly->first;

  while (t != NULL)
    {
      print_term (t, poly);
      t = t->next;
    }

  printf ("\n");
}

void
print_term (Term *pTerm, Polynomial *poly)
{
  if (pTerm->coef > 0 && pTerm != poly->first) //[+2x^5,+2x,+x^5,+x,+3]
    {
      if (pTerm->coef > 1 && pTerm->expo > 1)
        printf ("+%dx^%d", pTerm->coef, pTerm->expo);
      if (pTerm->coef > 1 && pTerm->expo == 1)
        printf ("+%dx", pTerm->coef);
      if (pTerm->coef == 1 && pTerm->expo > 1)
        printf ("+x^%d", pTerm->expo);
      if (pTerm->coef == 1 && pTerm->expo == 1)
        printf ("+x");
      if (pTerm->coef > 0 && pTerm->expo == 0)
        printf ("+%d", pTerm->coef);
    }

  else
    {
      if (pTerm->coef != 1 && pTerm->expo > 1)
        printf ("%dx^%d", pTerm->coef, pTerm->expo);
      if (pTerm->coef != 1 && pTerm->expo == 1)
        printf ("%dx", pTerm->coef);
      if (pTerm->coef == -1 && pTerm->expo > 1)
        printf ("-x^%d", pTerm->expo);
      if (pTerm->coef == 1 && pTerm->expo > 1)
        printf ("x^%d", pTerm->expo);
      if (pTerm->coef == -1 && pTerm->expo == 1)
        printf ("-x");
      if (pTerm->coef == 1 && pTerm->expo == 1)
        printf ("x");
      if (pTerm->expo == 0)
        printf ("%d", pTerm->coef);
    }
}

Polynomial *
findPolyByName (char poly_name)
{
  for (int i = 0; i < strlen (polys); i++)
    {
      if (polys[i]->name == poly_name)
        return polys[i];
    }

  return NULL;
}

void
insert_polynomial (Polynomial *ptr_poly)
{
  for (int i = 0; i < n; i++)
    {
      if (polys[i]->name == ptr_poly->name)
        {
          destroy_polynomial (polys[i]);
          polys[i] = ptr_poly;
          return;
        }
    }
  polys[n++] = ptr_poly;
}

void
destroy_polynomial (Polynomial *ptr_poly)
{
  if (ptr_poly == NULL)
    return;
  Term *t = ptr_poly->first, *tmp;

  while (t != NULL)
    {
      tmp = t;
      t = t->next;
      free (tmp);
    }

  free (ptr_poly);
}

Polynomial *
create_by_add_two_polynomials (char name, char f, char g)
{
  int c, e;
  Polynomial *new_p = create_polynomial_instance (name);
  Polynomial *p1 = NULL, *p2 = NULL;
  Term *new_t;
  Term *t1, *t2;

  for (int i = 0; i < n; i++)
    {
      if (polys[i]->name == f)
        p1 = polys[i];
      if (polys[i]->name == g)
        p2 = polys[i];
    }
  if (p1 == NULL || p2 == NULL)
    return NULL;

  new_t = new_p->first;
  t1 = p1->first;
  t2 = p2->first;

  while (p1 != NULL || p2 != NULL)
    {
      if (t1->expo == t2->expo)
        {
          c = (t1->coef) + (t2->coef);
          e = (t1->expo);
          add_term (c, e, new_p);
          t1 = t1->next;
          t2 = t2->next;
        }

      else
        {
          if (t1->expo > t2->expo)
            {
              c = t1->coef;
              e = t1->expo;
              add_term (c, e, new_p);
              t1 = t1->next;
            }

          else
            {
              c = t2->coef;
              e = t2->expo;
              add_term (c, e, new_p);
              t2 = t2->next;
            }
        }
    }

  return new_p;
}