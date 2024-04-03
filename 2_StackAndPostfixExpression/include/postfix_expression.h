#ifndef POST_FIXEXPRESSION_H
#define POST_FIXEXPRESSION_H
#include "stackADT.h"

static char OPERATORS_S[] = "+-*/()";
static Stack operand_stack;

int is_operator(char ch);
int eval(char *expr);
int eval_op(char op);
void handle_exception(const char *err_msg);

#endif
