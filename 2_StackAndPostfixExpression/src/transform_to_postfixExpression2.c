#define _CRT_SECURE_NO_WARNINGS
#include "transform_to_postfixExpression2.h"
#include "stackADT.h"

char *convert(char *infix) // 5 + 3ó�� �Ŀ� ������ �ִٰ� ����
{
    operator_stack = create();

    char *postfix = (char *)malloc(strlen(infix) + 1); // postfix expression�� ����� ���ڹ迭
    char *pos = postfix; // pos�� postfix�� pos�� ĭ������ ��ȯ�� ����ǥ����� ���� �迭�� ���ִٴ� ���̴�.

    char *token = strtok(infix, " ");
    while (token != NULL)
    {
        if (token[0] >= '0' && token[0] <= '9') // operand
        {
            sprintf(pos, "%s ", token);
            pos += (strlen(token) + 1);
        }

        else if (is_operator(token[0]) > -1) // operator
            pos = process_op(token[0], pos);

        else
            handle_exception("Syntax Error: Invalid character encountered.\n");

        token = strtok(NULL, " ");
    }
    while (!is_empty(operator_stack))
    {
        char op = (char)pop(operator_stack);
        if (op == '(')
            handle_exception("Unmatched parenthesis\n");
        sprintf(pos, "%c ", op);
        pos += 2;
    }
    *pos = '\0';
    return postfix;
}

char *process_op(char op, char *pos)
{
    if (is_empty(operator_stack) || op == '(')
        push(operator_stack, op);
    else
    { // ��� op�� ���� ��ȣ�� �ƴ�.
        char top_op = peek(operator_stack);
        if (precedence(op) > precedence(top_op)) //���� ���þȿ� ���� ��ȣ�� �ִٸ�, � �����ڵ� �׳� ����.
            push(operator_stack, op);
        else
        {
            //���� op�� ��ȣ��� �ݴ� ��ȣ�̴�.
            while (!is_empty(operator_stack) && precedence(op) <= precedence(top_op))
            {
                pop(operator_stack); // top_op�� �տ��� �̹� peek �����Ƿ� �ϴ� ������.
                if (top_op == '(')
                    break;
                sprintf(pos, "%c ", top_op);
                pos += 2;
                if (!is_empty(operator_stack))
                    top_op = (char)peek(operator_stack);
            }
            if (op != ')')
                push(operator_stack, op);
        }
    }

    return pos;
}

int precedence(char op)
{
    return PRECEDENCE[is_operator(op)];
}
