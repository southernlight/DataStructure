#include "stack.h"

#define INIT_CAPACITY 100
void reallocate(Stack s);

struct stack_type
{
    Item *contents;
    int top;
    int size;
};

static void terminate(const char *message)
{
    printf("%s\n", message);
    exit(1);
}

Stack create()
{
    Stack s = (Stack)malloc(sizeof(struct stack_type));
    if (s == NULL)
        terminate("Error in create s==NULL : stack could not be created.\n");
    s->contents = (Item *)malloc(INIT_CAPACITY * sizeof(Item));
    if (s->contents == NULL)
    {
        free(s);
        terminate("Error in create: s->contents == NULL : stack could not be created.\n");
    }
    s->top = -1;
    s->size = INIT_CAPACITY;
    return s;
}

void destroy(Stack s)
{
    free(s->contents);
    free(s);
}

void make_empty(Stack s)
{
    s->top = -1;
}

bool is_empty(Stack s)
{
    return s->top == -1;
}

bool is_full(Stack s)
{
    return s->top == s->size - 1;
}
void push(Stack s, Item i)
{
    if (is_full(s))
        reallocate(s);
    s->top++;
    s->contents[s->top] = i;
}

Item pop(Stack s)
{
    if (is_empty(s))
        terminate("Error in pop: stack is empty.\n");
    s->top--;
    return s->contents[s->top + 1];
}

Item peek(Stack s)
{
    if (is_empty(s))
        terminate("Error in peek: stack is empty.\n");
    return s->contents[s->top];
}

void reallocate(Stack s)
{
    printf("reallocate called\n");
    Item *tmp = (Item *)malloc(2 * s->size * sizeof(Item));
    if (tmp == NULL)
        terminate("Error in reallocate: stack could not be created.\n");

    for (int i = 0; i < s->size; i++)
        tmp[i] = s->contents[i];

    free(s->contents);
    s->contents = tmp;
    s->size *= 2;
    // if (tmp == NULL)
    //     terminate("Error in create reallocate : stack could not be created.\n");

    // for (int i = 0; i < s->size; i++)
    //     tmp[i] = s->contents[i];
    // free(s->contents);
    // s->contents = tmp;
    // s->size *= 2;
}