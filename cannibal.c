#include <stdlib.h>
#include <stdio.h>

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

static int cannibalize(int *nums, int num_nums, int query);
static int comp(const void *a, const void *b);

int main(void)
{
    int num_nums = 0;
    int num_queries = 0;

    scanf("%d%d", &num_nums, &num_queries);

    int nums[1024] = { 0 };

    for (int i = 0; i < num_nums; ++i)
    {
        scanf("%d", &nums[i]);
    }
    qsort(nums, num_nums, sizeof(int), comp);
    for (int i = 0; i < num_queries; ++i)
    {
        int query;

        scanf("%d", &query);
        printf("%d ", cannibalize(nums, num_nums, query));        
    }
    printf("\n");

    return EXIT_SUCCESS;
}

int cannibalize(int *nums, int num_nums, int query)
{
    int num_ge = 0;
    int i = 0;
   
    while (i < num_nums && nums[i] >= query)
    {
        ++num_ge;
        ++i;
    }

    int done_eating = FALSE;
    int j = num_nums - 1;

    do
    {
        int cannibal = nums[i];
        while (nums[i] > nums[j] && cannibal < query)
        {
            ++cannibal;
            --j;
        }
        if (nums[i] == cannibal)
        {
            done_eating = TRUE;
        }
        else if (cannibal < query)
        {
            nums[i] = cannibal;
        }
        else
        {
            ++num_ge;
            ++i;
        }
    } while (!done_eating);
    return num_ge;
}

int comp (const void *a, const void *b) 
{
    return *((int *) b) - *((int *) a);
}
