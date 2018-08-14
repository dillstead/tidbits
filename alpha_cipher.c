#include <stdlib.h>
#include <stdio.h>

#define MAX_SECRET 100

int main(void)
{
    char secret[MAX_SECRET] = { 0 };
    char c;
    int i = 0;

    while ((c = getchar()) != ' ')
    {
        secret[i++] = c;
    }

    int j = 0;
    while ((c = getchar()) != EOF && c != '\n')
    {
        printf("%c", 'a' + (secret[j] + c - 2 * 'a') % 26);
        j = (j + 1) % i;
    }
    printf("\n");

    return EXIT_SUCCESS;
}
