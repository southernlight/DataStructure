#include "queueADT.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    struct node *next;
    Item data;
} Node;

struct queue_type
{
    struct node *front, *rear;
    int size;
};

void terminate(const char *message)
{
    printf("%s\n", message);
    exit(1);
}

int get_size(Queue q)
{
    return q->size;
}

Queue create()
{
    Queue q = (Queue)malloc(sizeof(struct queue_type));
    if (q == NULL)
        terminate("Error in create: queue could not be created.\n");
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    return q;
}

void destroy(Queue q)
{
    make_empty(q); //������ ������ ���ֱ�
    free(q);
}

void make_empty(Queue q)
{
    while (!is_empty(q))
        dequeue(q);
    q->size = 0;
}

bool is_empty(Queue q)
{
    return q->front == NULL;
}

void enqueue(Queue q, Item i)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL)
        terminate("Error in push: queue is full.\n");
    new_node->data = i;
    new_node->next = NULL;

    if (q->front == NULL) // empty
    {
        q->front = new_node;
        q->rear = new_node;
    }

    else
    {
        q->rear->next = new_node;
        q->rear = new_node;
    }
    q->size++;
}

Item dequeue(Queue q)
{
    Node *old_front;
    Item i; // return �� ������

    if (q->front == NULL)
        terminate("Error in dequeue: queue is empty\n");
    old_front = q->front;
    i = old_front->data;
    q->front = old_front->next;

    if (q->front == NULL)
        q->rear = NULL;
    free(old_front);
    q->size--;
    return i;
}

Item peek(Queue q)
{
    if (is_empty(q))
        terminate("Error in peek: queue is empty.\n");
    return q->front->data;
}