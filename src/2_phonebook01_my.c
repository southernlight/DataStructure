#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#define CAPACITY 100

void add (void);
void find (char *name);
void status (void);
void delete (char *name);
void exit (void);

int
main ()
{
  char command[10];
  char *names[CAPACITY];
  char *numbers[CAPACITY];

  while (1)
    {
      printf ("$ ");
      scanf ("%s", command);

      if (!(strcmp ("add", command)))
        add ();
      else if (!(strcmp ("find", command)))
        printf ("find\n");
      else if (!(strcmp ("status", command)))
        printf ("status\n");
      else if (!(strcmp ("delete", command)))
        printf ("delete\n");
      else if (!(strcmp ("exit", command)))
        printf ("exit\n");

      while (getchar () != '\n')
        continue;
    }
}

void
add (void)
{
  ;
}