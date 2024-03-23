#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
Node *removeNode (Node *p);
void add_ordered_list (char *item);
Node *find (char *item);
// TODO: find 함수 만들기
int
main ()
{
  // test_code
  add_ordered_list ("a");
  add_ordered_list ("b");
  add_ordered_list ("e");
  add_ordered_list ("f");

  Node *tmp = head;
  while (tmp != NULL)
    {
      printf ("%s", tmp->data);
      tmp = tmp->next;
    }

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
removeNode (Node *p)
{
  if (head == NULL && tail == NULL)
    return NULL;
  else if (head == tail) // p가 유일한 노드인 경우
    {
      head = NULL;
      tail = NULL;
    }

  else if (p == head) // p가 head인 경우
    {
      p->next->prev = NULL;
      head = head->next;
    }

  else if (p == tail) // p가 tail인 경우
    {
      p->prev->next = NULL;
      tail = tail->prev;
    }

  else // 그 밖의 일반적인 경우
    {
      p->prev->next = p->next;
      p->next->prev = p->prev;
    }

  return p;
}

void
add_ordered_list (char *item)
{
  Node *p = tail;
  while (p != NULL && strcmp (item, p->data) < 0)
    p = p->prev;
  add_after (p, item);
}

Node *
find (char *item)
{
  ;
}