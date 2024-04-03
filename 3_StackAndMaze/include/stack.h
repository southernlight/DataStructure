#ifndef STACKADT_H
#define STACKADT_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int Item; // stack �ε� ������ �����ϰ��� �Ѵ�.
//���� �ڵ带 �����Ѵٰ� �Ҷ� �ѹ��� �ٲٸ� �ȴ�.
typedef struct stack_type *Stack;

Stack create();
void destroy(Stack s);
void make_empty(Stack s);
bool is_empty(Stack s);
void push(Stack s, Item i);
Item pop(Stack s);
Item peek(Stack s);
#endif