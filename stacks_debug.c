#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct item_t
{
    int size;
    int pos;
} item_t;

static bool pack(item_t *items, int num_items, int bin_size, int sum, int item_pos, int pos);
static void print(item_t *items, int num_items, int bin_size);

int main(void)
{
    int num_bins;
    item_t items[128] = { { 0 } };
    int num_items = 0;
    int bin_size = 0;
    
    scanf("%d", &num_bins);
    while (scanf("%1d", &items[num_items].size) == 1)
    {
        bin_size += items[num_items].size;
        num_items++;
    }
    bin_size /= num_bins;

    bool done_pack = pack(items, num_items, bin_size, 0, 0, 1);

    if (done_pack)
    {
        print(items, num_items, bin_size);
    }
    else
    {
        printf("no solution");
    }
    printf("\n");

    return EXIT_SUCCESS;
}

bool pack(item_t *items, int num_items, int bin_size, int sum, int item_pos, int pos)
{
    sum += items[item_pos].size;
    //printf("sum: %d, item_pos: %d, pos: %d, bin_size: %d\n", sum, item_pos, pos, bin_size);
    //printf("item size: \n");
    //for (int i = 0; i < num_items; i++)
    //{
    //    printf("%d ", items[i].size);
    //}
    //printf("\n");

    if (sum > bin_size)
    {
        printf("bt sum: %d, item_pos: %d, pos: %d, bin_size: %d\n", sum, item_pos, pos, bin_size);
        for (int i = 0; i < num_items; i++)
        {
            printf("%d ", items[i].size);
        }
        printf("\n");
        for (int i = 0; i < num_items; i++)
        {
            if (i == item_pos)
            {
                printf("%d ", pos);
            }
            else
            {
                printf("%d ", items[i].pos);
            }
        }
        printf("\n");
        //print(items, num_items, bin_size);
        //printf("%d\n", items[item_pos].size);
        //printf("pos: ");
        return false;
    }

    items[item_pos].pos = pos;
    printf("step sum: %d, item_pos: %d, pos: %d, bin_size: %d\n", sum, item_pos, pos, bin_size);
    for (int i = 0; i < num_items; i++)
    {
        printf("%d ", items[i].size);
    }
    printf("\n");
    for (int i = 0; i < num_items; i++)
    {
        printf("%d ", items[i].pos);
    }
    printf("\n");

    int start_pos = item_pos + 1;
    if (sum == bin_size)
    {
        if (pos == num_items)
        {
            printf("success\n");
            //print(items, num_items, bin_size);
            //printf("\n");
            return true;
        }
        sum = 0;
        start_pos = 0;
    }
    
    bool done_pack = false;
    for (int i = 0; !done_pack && i < num_items; i++)
    {
        if (items[i].pos == 0)
        {
            done_pack = pack(items, num_items, bin_size, sum, i, pos + 1);
        }
    }

    if (!done_pack)
    {
        items[item_pos].pos = 0;
    }

    return done_pack;
}

void print(item_t *items, int num_items, int bin_size)
{
    int sol[128] = { 0 };
    int num_sol = 0;

    for (int i = 0; i < num_items; i++)
    {
        if (items[i].pos > 0)
        {
            num_sol++;
            sol[items[i].pos - 1] = items[i].size;
        }
    }
    for (int i = 0, total_size = 0; i < num_sol; i++)
    {
        total_size += sol[i];
        printf((total_size % bin_size) ? "%d" : "%d ",  sol[i]);
    }
}
