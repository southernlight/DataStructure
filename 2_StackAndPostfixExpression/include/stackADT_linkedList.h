#ifndef STACKADT_LINKEDLIST_H
#define STACKADT_LINKEDLIST_H
#include <stdbool.h>
typedef int Item;
typedef struct stack_type* Stack;

static Stack create();
static void destroy(Stack s);
static void make_empty(Stack s);
static bool is_empty(Stack s);
static void push(Stack s, Item i);
static Item pop(Stack s);
#endif