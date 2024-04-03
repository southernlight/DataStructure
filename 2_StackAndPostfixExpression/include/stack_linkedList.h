#ifndef STACK_LINKEDLIST_H
#define STACK_LINKEDLIST_H
#include <stdio.h>
#include <stdlib.h>

struct node
{
    char *data;
    struct node *next;
};
typedef struct node Node;

Node *top = NULL;

static void push(char *item);
static char *pop();
static char *peek();
static int is_empty();
#endif