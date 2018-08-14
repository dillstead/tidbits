#include <stdio.h>
#include <stdlib.h>

int bs(int n);

int main(void)
{
    int num;

    scanf("%d", &num);

    for (int n = 0; n < num; n++)
    {
        printf("%d, ", bs(n));
    }
    printf("%d\n", bs(num));

    return EXIT_SUCCESS;
}

int bs(int n)
{
    int cnt = 0;

    while (n)
    {
        if (n & 0x01)
        {
            if (cnt & 0x01)
            {
                return 0;
            }
            cnt = 0;
        }
        else
        {
            cnt++;
        }
        n >>= 1;
    }

    return 1;
}
