#include <stdio.h>
#include <stdlib.h>

static unsigned int masks[26];

typedef struct resource_t
{
    int total;
    unsigned int mask;
} resource_t;

int main(void)
{
    for (int i = 0; i < 26; i++)
    {
        masks[i] = 1 << i;
    }

    scanf("Cards [");
    int c;

    while (c != '.')
    {
        
    }
    return EXIT_SUCCESS;
}

// Cards [W/B/S/O, W, S/B, S]. Can you make WWSS?
