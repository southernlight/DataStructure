#define _CRT_SECURE_NO_WARNINGS
#include "postfix_expression.h"
#include "transform_to_postfixExpression2.h"

#define MAX_LENGTH 100

void read_line(FILE *fp, char line[], int limit)
{
    int i = 0;
    char ch;
    while ((ch = fgetc(fp)) != '\n')
    {
        if (i < limit - 1)
            line[i++] = ch;
    }
    line[i] = '\0';
}

int main()
{
    char infix[MAX_LENGTH];
    read_line(stdin, infix, MAX_LENGTH);

    printf(" %s := ", infix);
    char *postfix = convert(infix);
    printf(" %d\n", eval(postfix));
}