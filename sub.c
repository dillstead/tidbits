#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char sc = 0xFF;
    char out[8];
    
    for (int i = 7; i >= 0; i--)
    {
        out[i] = sc & 0x01 ? '1' : '0';
        sc >>= 1;
    }
    char t = 0x81 - 0x7F;
    printf("%d\n", t);
    printf("%u\n", t);

    t = 0xFF - 0x1;
    printf("%d\n", t);
    printf("%u\n", t);

    t = 0x01 - 0xFF;
    printf("%d\n", t);
    printf("%u\n", t);


    return EXIT_SUCCESS;
}
