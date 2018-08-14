#include <stdlib.h>
#include <stdio.h>

#define MAX_COMPLEX  1024
#define min(X,Y)     ((X) < (Y) ? (X) : (Y))

int main(void)
{
    int complex[MAX_COMPLEX] = { 0 };
    int sum = 0;
    int num_complex;

    scanf("%d", &num_complex);

    for (int i = 1; i < num_complex + 1; i++)
    {
        int mc = complex[i] = i;

        for (int j = 1; j <= i / 4 + 1; j++)
        {
            // 1 * 1
            if (i % j == 0)
            {
                mc = min(mc, complex[j] + complex[i / j]);
            }
        }
        for (int j = 0; j <= i / 2; j++)
        {
            // 0 + 1
            mc = min(mc, complex[j] + complex[i - j]);
        }
        complex[i] = mc;
        sum += mc;
    }

    for (int i = 1; i < num_complex + 1; i++)
    {
        printf("%d ", complex[i]);
    }
    printf("\n");
    printf("%d\n", sum);
    
    return EXIT_SUCCESS;
}
