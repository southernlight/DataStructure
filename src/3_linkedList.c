#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
typedef struct node
{
  char *data;
  struct node *next;
} Node;

head = NULL;

int add_first (Node **head_ptr, char *item);
int add_after (Node *prev, char *item);
Node *remove_first ();

int
main ()
{
  ;

  return 0;
}

int
add_first (Node **head_ptr, char *item)
{
  Node *tmp = (Node *)malloc (sizeof (Node));
  tmp->data = item;
  tmp->next = *head_ptr;
  *head_ptr = tmp;
}

int
add_after (Node *prev, char *item)
{
  if (prev == NULL)
    return 0;
  Node *tmp = (Node *)malloc (sizeof (Node));
  tmp->data = item;
  tmp->next = prev->next;
  prev->next = tmp;

  return 1;
}

Node *
remove_first ()
{
  if (head == NULL)
    return NULL;
  else
    {
      ;
    }
}