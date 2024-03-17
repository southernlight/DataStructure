#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
  char *data;
  struct node *next;
} Node;

Node *head = NULL;

void add_first (char *item);
void add_first_local (Node **head_ptr, char *item);
int add_after (Node *prev, char *item);
Node *remove_first ();
Node *remove_after (Node *prev);
Node *find (char *word);
Node *get_node (int index);
int add (int index, char *item);
Node *removeByindex (int index);
Node *removeByitem (char *item);
void add_to_ordered_list (char *item);

int
main ()
{
  ;

  return 0;
}

void
add_first (char *item)
{
  Node *tmp = (Node *)malloc (sizeof (Node));
  if (tmp == NULL)
    return;
  tmp->data = item;
  tmp->next = head->next;
  head = tmp;
}

void
add_first_local (Node **head_ptr, char *item)
{
  Node *tmp = (Node *)malloc (sizeof (Node));
  if (tmp == NULL)
    return;
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

  if (tmp == NULL)
    return 0;
  tmp->data = item;
  tmp->next = prev->next;
  prev->next = tmp;

  return 1;
}

Node *
remove_first () // 필요하면 tmp를 free 시켜 삭제해주어야 한다.
{
  if (head == NULL)
    return NULL;
  else
    {
      Node *tmp = head;
      head = head->next;
      return tmp;
    }
}

Node *
remove_after (Node *prev)
{
  Node *tmp = prev->next;
  if (tmp == NULL)
    {
      return NULL;
    }

  else
    {
      prev->next = prev->next->next;
    }
  return tmp;
}

Node *
find (char *word)
{
  Node *p = head;
  while (p != NULL)
    {
      if (strcmp (p->data, word) == 0)
        return p;
      p = p->next;
    }

  return NULL;
}

Node *
get_node (int index)
{
  if (index < 0)
    return NULL;
  Node *p = head;

  for (int i = 0; i < index && p != NULL; i++)
    p = p->next;
  return p;
}

int
add (int index, char *item)
{
  if (index < 0)
    return 0;

  if (index == 0)
    {
      add_first (item);
      return 1;
    }

  Node *prev = get_node (index - 1);
  if (prev != NULL)
    {
      add_after (prev, item);
      return 1;
    }
  return 0;
}

Node *
removeByindex (int index)
{
  if (index < 0)
    return NULL;
  if (index == 0)
    return remove_first ();

  Node *prev = get_node (index - 1);
  if (prev == NULL)
    return NULL;
  else
    remove_after (prev);
}

Node *
removeByitem (char *item)
{
  Node *p = head;
  Node *q = NULL;
  while (p != NULL && strcmp (p->data, item) != 0)
    {
      q = p;
      p = p->next;
    }

  if (p == NULL)
    return NULL;
  if (q == NULL)
    return remove_first ();
  else
    return remove_after (q);
}

void
add_to_ordered_list (char *item)
{
  Node *p = head;
  Node *q = NULL;

  while (p != NULL && strcmp (p->data, item) <= 0)
    {
      q = p;
      p = p->next;
    }

  if (q != NULL)
    add_first (item);
  else
    add_after (q, item);
}
