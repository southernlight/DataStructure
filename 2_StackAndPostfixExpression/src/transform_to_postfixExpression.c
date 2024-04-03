#include "transform_to_postfixExpression.h"

static char *convert(char *infix) // 5 + 3ó�� �Ŀ� ������ �ִٰ� ����
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
        {
            //�����ڴ� ���ÿ� push �Ѵ�.
            //�� ���� ���� �켱������ �ڽź��� ���� �����ڰ� ������ pop�Ͽ� ����� �� push�Ѵ�. ���� pos �ʿ�
            // process_op���� ó���� �� �Ŀ� ���� pos ���� �ٲ�����ϱ� ������ return ������ �ٲ� ���� �ٽ�
            // �޴´�.
            pos = process_op(token[0], pos);
        }

        else
            handle_exception("Syntax Error: Invalid character encountered.\n");

        token = strtok(NULL, " ");
    }
    while (!is_empty(operator_stack))
    {
        char op = (char)pop(operator_stack);
        sprintf(pos, "%c ", op);
        pos += 2;
    }
    *pos = '\0';
    return postfix;
}

static char *process_op(char op, char *pos)
{
    if (is_empty(operator_stack))
        push(operator_stack, op);
    else
    {
        char top_op = peek(operator_stack);
        if (precedence(op) > precedence(top_op)) //���� ���� ���� �켱������ �� ū ���
            push(operator_stack, op);
        else
        {
            while (!is_empty(operator_stack) && precedence(op) <= precedence(top_op))
            {
                pop(operator_stack); // top_op�� �տ��� �̹� peek �����Ƿ� �ϴ� ������.
                sprintf(pos, "%c ", top_op);
                pos += 2;
                if (!is_empty(operator_stack))
                    top_op = (char)peek(operator_stack);
            }

            push(operator_stack, op);
        }
    }

    return pos;
}

static int precedence(char op)
{
    return PRECEDENCE[is_operator(op)];
}
