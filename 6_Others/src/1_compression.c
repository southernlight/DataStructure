#define _CRT_SECURE_NO_WARNINGS

#include <ctype.h> //isspace function
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 100

int read_line_with_compression(char compressed[], int limit);

int main(void)
{
    char line[BUFFER_SIZE];
    int length;

    while (1)
    {
        printf("$ ");
        length = read_line_with_compression(line, BUFFER_SIZE);
        printf("%s:%d\n", line, length);
    }
}

int read_line_with_compression(char compressed[], int limit)
{
    int ch, i = 0;
    while ((ch = getchar()) != '\n')
    {
        if (i < limit - 1 && (!isspace(ch) || i > 0 && !isspace(compressed[i - 1])))
            compressed[i++] = ch;
    }

    if (i > 0 && isspace(compressed[i - 1]))
        i--;
    compressed[i] = '\0';

    return i;
}
