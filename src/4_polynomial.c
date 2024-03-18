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
int compress (char *str);

void add_term (int c, int e, Polynomial *poly);
Term *remove_first (Polynomial *poly);
Term *remove_after (Term *prev);
void add_first (int c, int e, Polynomial *poly);
void add_after (int c, int e, Term *prev);
int eval_poly (Polynomial *poly, int x);
int eval_term (Term *, int x);
Polynomial *findPolyByName (char poly_name);

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
  int length;
  length = compress (expression);
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
}

int
parse_and_add_term (char *expr, int begin, int end, int polynomial)
{
  int buffer_index = 0;
  char buffer_coef[BUFFER_SIZE];
  char buffer_expo[BUFFER_SIZE];

  int sign_coef = 1;      // 0: 음수 1: 양수
  int coef = 0, expo = 1; // coef 는 계수의 절댓값
  if (expr[begin] == '+' || (expr[begin] >= '1' && expr[begin] <= '9'))
    sign_coef = 1; // 양수
  else if (expr[begin] == '-')
    sign_coef = 0; // 음수

  for (int i = begin; i < end; i++)
    {
      if (expr[i] >= '0' && expr[i] <= '9')
        buffer_coef[buffer_index++] = expr[i];
      if (expr[i] == 'x' || '^')
        break;
    }
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

  Term *p = poly->first;
  Term *q = NULL;

  while (p != NULL && p->expo > e)
    {
      q = p;
      p = p->next;
    }
  // 동일 차수의 항이 존재하는 경우
  if (p->expo == e)
    {
      if ((p->expo + e) == 0)
        {
          if (q == NULL)
            remove_first (poly);
          remove_after (q);
          free (p);
        }
      else
        {
          p->coef += c;
        }
    }
  // 동일 차수의 항이 존재하지 않는 경우
  else
    {
      if (q == NULL) // 맨 앞에 삽입
        add_first (c, e, poly);
      else
        add_after (c, e, q);
    }
}

Term *
remove_first (Polynomial *poly)
{
  Term *head = poly->first;
  if (head == NULL)
    return NULL;
  else
    {
      poly->first = head->next;
      return head;
    }
}

Term *
remove_after (Term *prev)
{
  Term *t = prev->next;
  if (t == NULL)
    {
      return NULL;
    }

  else
    {
      prev->next = t->next;
    }

  return t;
}

void
add_first (int c, int e, Polynomial *poly)
{
  Term *head = poly->first;
  Term *t = create_term_instance ();
  t->coef = c;
  t->expo = e;
  t->next = head->next;
  head->next = t;
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
print_poly (Polynomial *p)
{
  const Term *head = p->first;
  Term *t = head;

  while (t != NULL)
    {
      print_term (t, head);
      t = t->next;
    }
}

void
print_term (Term *pTerm, const Term *head)
{
  // 일반항
  if (pTerm->expo != 0)
    {
      if (pTerm->coef >= 0 && pTerm != head)
        printf ("+%dx^%d", pTerm->coef, pTerm->expo);
      else
        printf ("%dx^%d", pTerm->coef, pTerm->expo);
    }
  // 상수항
  else
    {
      if (pTerm->coef >= 0 && pTerm != head)
        printf ("+%d", pTerm->coef);
      else
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
