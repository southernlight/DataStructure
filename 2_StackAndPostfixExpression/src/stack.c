#include "stack.h"
#define MAX_CAPACITY 100

char stack[MAX_CAPACITY];
static int top = -1;

static void push(char ch)
{
    if (is_full())
        return;
    top++;
    stack[top] = ch;
}

static char pop()
{
    if (is_empty())
        return 0;
    char tmp = stack[top];
    top--;
    return tmp;
}

static char peek()
{
    if (is_empty())
        return 0;
    return stack[top];
}

static int is_empty()
{
    return top == -1;
}

static int is_full()
{
    return top == MAX_CAPACITY - 1;
}
