#include "stack_linkedList.h"

static void push(char *item)
{
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = item;
    p->next = top;
    top = p;
}

static char *pop()
{
    if (is_empty())
        return NULL;
    char *result = top->data;
    Node *p = top;
    top = top->next;
    free(p);
    return result;
}

static char *peek()
{
    if (is_empty())
        return NULL;
    return top->data;
}

static int is_empty()
{
    return top == NULL;
}