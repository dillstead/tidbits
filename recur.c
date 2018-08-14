#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void)
{
    int c;
    bool seen[256] = { 0 };

    while ((c = getchar()) != EOF)
    {
        if (seen[c])
        {
            printf("%c\n", c);
            break;
        }
        seen[c] = true;
    }

    return EXIT_SUCCESS;
}
