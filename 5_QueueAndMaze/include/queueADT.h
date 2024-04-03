#ifndef QUEUEADT_H
#define QUEUEADT_H

#include "pos.h"
#include <stdbool.h>

typedef Position Item;

typedef struct queue_type *Queue;

Queue create();
void destroy(Queue q);
void make_empty(Queue q);
bool is_empty(Queue q);
void enqueue(Queue q, Item i);
Item dequeue(Queue q);
Item peek(Queue q);
int get_size(Queue q);
void reallocate(Queue q);

#endif
