#include "transform_to_postfixExpression.h"

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
        {
          // 연산자는 스택에 push 한다.
          // 단 스택 내에 우선순위가 자신보다 높은 연산자가 있으면 pop하여
          // 출력한 후 push한다. 따라서 pos 필요 process_op에서 처리를 한 후에
          // 원래 pos 값을 바꿔줘야하기 때문에 return 값으로 바뀐 값을 다시
          // 받는다.
          pos = process_op (token[0], pos);
        }

      else
        handle_exception ("Syntax Error: Invalid character encountered.\n");

      token = strtok (NULL, " ");
    }
  while (!is_empty (operator_stack))
    {
      char op = (char)pop (operator_stack);
      sprintf (pos, "%c ", op);
      pos += 2;
    }
  *pos = '\0';
  return postfix;
}

char *
process_op (char op, char *pos)
{
  if (is_empty (operator_stack))
    push (operator_stack, op);
  else
    {
      char top_op = peek (operator_stack);
      if (precedence (op)
          > precedence (top_op)) // 지금 들어가는 값이 우선순위가 더 큰 경우
        push (operator_stack, op);
      else
        {
          while (!is_empty (operator_stack)
                 && precedence (op) <= precedence (top_op))
            {
              pop (operator_stack); // top_op를 앞에서 이미 peek 했으므로 일단
                                    // 버린다.
              sprintf (pos, "%c ", top_op);
              pos += 2;
              if (!is_empty (operator_stack))
                top_op = (char)peek (operator_stack);
            }

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
