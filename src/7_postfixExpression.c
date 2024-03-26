#include "postfix_expression.h"
#include <stdio.h>

static char OPERATORS[] = "+-*/";
Stack operand_stack;

int
is_operator (char ch)
{
  for (int i = 0; i < strlen (OPERATORS); i++)
    {
      if (OPERATORS[i] == ch)
        return i;
    }
  return -1;
}

int
eval (char *expr)
{
  int value = 0;
  int result = 0;
  operand_stack = create ();
  char *token = strtok (expr, " ");
  while (token != NULL)
    {
      if (token[0] >= '0' && token[0] <= '9') // 피연산자
        {
          value = atoi (token);
          push (operand_stack, value);
        }
      else if (is_operator (token[0]) > -1) // 연산자
        {
          result = eval_op (token[0]);
          push (operand_stack, result);
        }

      else
        handle_exception ("Syntax Error:invalid character encountered");
      token = strtok (NULL, " ");
    }

  if (is_empty (operand_stack))
    handle_exception ("Syntax Error: Stack empty in eval_op");
}

int
eval_op (char op)
{
  if (is_empty (operand_stack))
    handle_exception ("Syntax Error: Stack empty in eval_op");
  int rhs = pop (operand_stack);
  if (is_empty (operand_stack))
    handle_exception ("Syntax Error: Stack empty in eval_op");
  int lhs = pop (operand_stack);
  int result = 0;

  switch (op)
    {
    case '+':
      result = lhs + rhs;
      break;
    case '-':
      result = lhs - rhs;
      break;
    case '*':
      result = lhs * rhs;
      break;
    case '/':
      result = lhs / rhs;
      break;
    }

  return result;
}

void
handle_exception (const char *err_msg)
{
  printf ("%s\n", err_msg);
  exit (1);
}