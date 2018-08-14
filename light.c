#include <stdlib.h>
#include <stdio.h>

#define MAX_INT(a,b) (((a) > (b)) ? (a) : (b))

static int comp(const void *a, const void *b);

int main(void)
{
    int in[1024];
    int out[1024];
    int inout_len = 0;

    while (scanf("%d%d", &in[inout_len], &out[inout_len]) == 2)
    {
        inout_len++;
    }
    qsort(in, inout_len, sizeof(int), comp);
    qsort(out, inout_len, sizeof(int), comp);

    int time_on = 0;
    int in_room = 0;
    int total_on = 0;
    int i = 0, j = 0;

    while (i < inout_len && j < inout_len)
    {
        if (in[i] <= out[j])
        {
            if (in_room == 0)
            {
                time_on = in[i];
            }
            in_room++;
            i++;
        }
        else if (out[j] < in[i])
        {
            if (in_room == 1)
            {
                total_on += out[j] - time_on;
            }
            in_room--;
            j++;
        }
    }
    printf("%d\n", total_on + out[inout_len - 1] - time_on);

    return EXIT_SUCCESS;
}

int comp(const void *a, const void *b) 
{
    return *((int *) a) - *((int *) b);
}
