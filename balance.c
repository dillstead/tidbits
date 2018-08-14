#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int trans[128];
    int before[128];
    int num_trans;
    int sum = 0;

    scanf("%d", &num_trans);
    for (int i = 0; i < num_trans; i++)
    {
        scanf("%d", &trans[i]);
        before[i] = sum;
        sum += trans[i];
    }
    sum = 0;
    for (int i = num_trans - 1; i >= 0; i--)
    {
        if (before[i] == sum)
        {
            printf("%d ", i);            
        }
        sum += trans[i];
    }
    printf("\n");

    return EXIT_SUCCESS;
}
