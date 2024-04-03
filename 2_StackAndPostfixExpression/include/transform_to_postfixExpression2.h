#ifndef TRANSFOR_TO_POSTFIXEXPRESSION2_H
#define TRANSFOR_TO_POSTFIXEXPRESSION_H
#define _CRT_SECURE_NO_WARNINGS
#include "postfix_expression.h"
#include <stdlib.h>
#include <string.h>

static char OPERATORS[] = "+-*/()";
//���� ��ȣ �켱������ -1�� �ϸ� ���� ��ȣ�� ������ ������ ���ÿ� ������ �ǰ�
//���� ��ȣ�� top�� ������ �ƹ��͵� pop ���� �ʴ´�.
static int PRECEDENCE[] = {1, 1, 2, 2, -1, -1};

static Stack operator_stack;

char *convert(char *infix);
char *process_op(char op, char *pos);
int precedence(char op);
#endif