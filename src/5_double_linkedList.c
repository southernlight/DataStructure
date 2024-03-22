#include <stdio.h>

typedef struct node
{
  char *data;
  struct node *next;
  struct node *prev;
} Node;
Node *head;
Node *tail;
int size = 0; // the number of Nodes.

void add_after (Node *pre, char *item);
Node *remove (Node *p);

// TODO: remove 만들기
int
main ()
{
  return 0;
}

void
add_after (Node *pre, char *item)
{
  Node *new_node = (Node *)malloc (sizeof (Node));
  new_node->data = item;
  new_node->prev = NULL;
  new_node->next = NULL;

  if (pre == NULL && head == NULL) // to empty list
    {
      head = new_node;
      tail = new_node;
    }

  else if (pre == NULL) // at the head
    {
      new_node->next = head;
      head->prev = new_node;
      head = new_node;
    }

  else if (pre == tail) // at the tail
    {
      new_node->prev = tail;
      tail->next = new_node;
      tail = new_node;
    }

  else // in the middle
    {
      new_node->prev = pre;
      new_node->next = pre->next;
      pre->next->prev = new_node;
      pre->next = new_node;
    }

  size++;
}

Node *
remove (Node *p)
{
  if (head == NULL && tail == NULL)
    return NULL;
  else if (head == tail)
    {
      head = NULL;
      tail = NULL;
      free (p);
    }
}