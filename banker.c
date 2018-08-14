#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_RES   100
#define MAX_PROC  25

static int get_seq(int avail[], int num_res, int *alloc[], int *max[], int num_proc,
                   int seq[]);

int main(void)
{
    int avail[MAX_RES];
    int num_res = 0;

    scanf("[");
    while (scanf("%d", &avail[num_res]) == 1)
    {
        num_res++;
    }
    scanf("]\n");

    int *alloc[MAX_PROC];
    int *max[MAX_PROC];
    int num_proc = 0;
    int temp;
    while (scanf("[%d", &temp) == 1)
    {
        alloc[num_proc] = (int *)malloc(sizeof(int) * num_res);
        max[num_proc] = (int *)malloc(sizeof(int) * num_res);
        alloc[num_proc][0] = temp;
        for (int i = 1; i < num_res; i++)
        {
            scanf("%d", &alloc[num_proc][i]);
        }
        for (int i = 0; i < num_res - 1; i++)
        {
            scanf("%d", &max[num_proc][i]);
        }
        scanf("%d]\n", &max[num_proc][num_res - 1]);
        num_proc++;
    }

    int seq[MAX_PROC];
    int num_seq = get_seq(avail, num_res, alloc, max, num_proc, seq);
    if (num_seq == num_proc)
    {
        for (int i = 0; i < num_seq; i++)
        {
            printf("P%d ", seq[i]);
        }
        printf("\n");
    }
    else
    {
        printf("Bad state\n");
    }

    for (int i = 0; i < num_proc; i++)
    {
        free(alloc[i]);
        free(max[i]);
    }

    return EXIT_SUCCESS;
}

int get_seq(int avail[], int num_res, int *alloc[], int *max[], int num_proc,
            int seq[])
{
    int num_seq = 0;
    bool fin[MAX_PROC] = { 0 };
    int num_fin = 1;

    while (num_fin)
    {
        num_fin = 0;
        for (int i = 0; i < num_proc; i++)
        {
            if (!fin[i])
            {
                //printf("Checking %d\n", i);
                int j = 0;
                while (j < num_res && max[i][j] - alloc[i][j] <= avail[j])
                {
                    j++;
                }
                if (j == num_res)
                {
                    fin[i] = true;
                    for (int k = 0; k < num_res; k++)
                    {
                        avail[k] += alloc[i][k];
                    }
                    //printf("Finished %d\n", i);
                    seq[num_seq++] = i;
                    num_fin++;
                }
            }
        }
    }
        
    return num_seq;
}
