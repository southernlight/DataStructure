
#define MAX_CAPACITY 100

char stack[MAX_CAPACITY];
int top = -1;

void
push (char ch)
{
  if (is_full ())
    return;
  top++;
  stack[top] = ch;
}

char
pop ()
{
  if (is_empty ())
    return;
  char tmp = stack[top];
  top--;
  return tmp;
}

int
is_empty ()
{
  return top == -1;
}

int
is_full ()
{
  return top == MAX_CAPACITY - 1;
}

int
main ()
{
  ;
}