#include <stdio.h>
#include <stdlib.h>
#include "queueADT.h"

#define INIT_CAPACITY 100

struct queue_type
{
	Item* contents;
	int front;
	int rear;
	int size; //저장된 데이터의 개수
	int capacity; //배열 contents의 크기
};

void terminate(const char* message)
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
	q->contents = (Item*)malloc(INIT_CAPACITY * sizeof(Item));
	if (q->contents == NULL)
	{
		terminate("Error in create: queue could not be created.\n");
		free(q);
	}

	q->front = 0;
	q->rear = -1; //왜 rear를 -1로 했을까? ->
	q->size = 0;
	q->capacity = INIT_CAPACITY;
	return q;
}

void destroy(Queue q)
{
	free(q->contents);
	free(q);
}

void make_empty(Queue q) //Queue를 완전히 없애는 것이 아니라 Queue를 비우는 것만 한다.
{
	q->front = 0;
	q->rear = -1;
	q->size = 0;
}

bool is_empty(Queue q)
{
	return q->size == 0;
}

bool is_full(Queue q)
{
	return q->size == q->capacity;
}

void enqueue(Queue q, Item i)
{
	if (is_full(q))
		reallocate(q);
	q->rear = (q->rear + 1) % (q->capacity); // circular 하게 돌아오는 것을 표현할 때 자주 쓰이는 것.
	q->contents[q->rear] = i;
	q->size++;
}

Item dequeue(Queue q)
{
	if (is_empty(q))
		terminate("Error in dequeue: queue is empty\n");
	Item result = q->contents[q->front];
	q->front = (q->front + 1) % (q->capacity);
	q->size--;
	return result;
}

Item peek(Queue q)
{
	if (is_empty(q))
		terminate("Error in peek: queue is empty.\n");
	return q->contents[q->front];

}

void reallocate(Queue q)
{
	Item* tmp = (Item*)malloc(2 * q->capacity * sizeof(Item));
	if (tmp == NULL)
		terminate("Error in reallocate: queue could not be reallocated.\n");
	int j = q->front;

	for (int i = 0; i < q->size; i++)
	{
		tmp[i] = q->contents[j];
		j = (j + 1) % (q->capacity); //단순히 j++가 아님.
	}
	free(q->contents);

	q->front = 0;
	q->rear = q->size - 1;
	q->contents = tmp;
	q->capacity *= 2;

}