#define _CRT_SECURE_NO_WARNINGS
#include "stackADT.h"
#include "transform_to_postfixExpression2.h"

char *
convert (char *infix) // 5 + 3처럼 식에 공백이 있다고 가정
{
  operator_stack = create ();

  char *postfix = (char *)malloc (strlen (infix)
                                  + 1); // postfix expression이 저장될 문자배열
  char *pos = postfix; // pos는 postfix는 pos앞 칸까지는 변환된 후위표기식이
                       // 동적 배열에 들어가있다는 뜻이다.

  char *token = strtok (infix, " ");
  while (token != NULL)
    {
      if (token[0] >= '0' && token[0] <= '9') // operand
        {
          sprintf (pos, "%s ", token);
          pos += (strlen (token) + 1);
        }

      else if (is_operator (token[0]) > -1) // operator
        pos = process_op (token[0], pos);

      else
        handle_exception ("Syntax Error: Invalid character encountered.\n");

      token = strtok (NULL, " ");
    }
  while (!is_empty (operator_stack))
    {
      char op = (char)pop (operator_stack);
      if (op == '(')
        handle_exception ("Unmatched parenthesis\n");
      sprintf (pos, "%c ", op);
      pos += 2;
    }
  *pos = '\0';
  return postfix;
}

char *
process_op (char op, char *pos)
{
  if (is_empty (operator_stack) || op == '(')
    push (operator_stack, op);
  else
    { // 적어도 op는 여는 괄호는 아님.
      char top_op = peek (operator_stack);
      if (precedence (op)
          > precedence (top_op)) // 현재 스택안에 여는 괄호가 있다면, 어떤
                                 // 연산자도 그냥 들어간다.
        push (operator_stack, op);
      else
        {
          // 만약 op가 괄호라면 닫는 괄호이다.
          while (!is_empty (operator_stack)
                 && precedence (op) <= precedence (top_op))
            {
              pop (operator_stack); // top_op를 앞에서 이미 peek 했으므로 일단
                                    // 버린다.
              if (top_op == '(')
                break;
              sprintf (pos, "%c ", top_op);
              pos += 2;
              if (!is_empty (operator_stack))
                top_op = (char)peek (operator_stack);
            }
          if (op != ')')
            push (operator_stack, op);
        }
    }

  return pos;
}

int
precedence (char op)
{
  return PRECEDENCE[is_operator (op)];
}

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

void
handle_exception (const char *err_msg)
{
  printf ("%s\n", err_msg);
  exit (1);
}