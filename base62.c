#include <stdlib.h>
#include <stdio.h>

static const char *map = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
static void conv(unsigned long long num);

int main(void)
{
    unsigned long long num; 

    while (scanf("%llu", &num) == 1)
    {
        conv(num);
        printf("\n");
    }

    return EXIT_SUCCESS;
}

void conv(unsigned long long num)
{
    unsigned int r = num % 62;
    unsigned long long d = num / 62;

    if (d != 0)
    {
        conv(d);
    }
    printf("%c", map[r]);
}


