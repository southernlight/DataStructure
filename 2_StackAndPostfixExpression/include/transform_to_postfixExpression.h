#ifndef TRANSFORM_TO_POSTFIXEXPRESSION_H
#define TRANSFORM_TO_POSTFIXEXPRESSION_H
#include "postfix_expression.h"
#include <stdlib.h>
#include <string.h>
static int PRECEDENCE[] = {1, 1, 2, 2}; //�������� �켱����

static Stack operator_stack; // char type�̾�� �ϴµ� C���� char type�� int type�� ȣȯ���� �ִ�.

static char *convert(char *infix);
static char *process_op(char op, char *pos);
static int precedence(char op);
#endif