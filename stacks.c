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

    if (pack(items, num_items, bin_size, 0, 0, 1))
    {
        print(items, num_items, bin_size);
    }
    else
    {
        printf("no solution\n");
    }

    return EXIT_SUCCESS;
}

bool pack(item_t *items, int num_items, int bin_size, int sum, int item_pos, int pos)
{
    sum += items[item_pos].size;

    if (sum > bin_size)
    {
        return false;
    }

    items[item_pos].pos = pos;
    int start_pos = item_pos + 1;

    if (sum == bin_size)
    {
        if (pos == num_items)
        {
            return true;
        }
        start_pos = 0;
        sum = 0;
    }
    
    bool done_pack = false;
    for (int i = start_pos; !done_pack && i < num_items; i++)
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

    for (int i = 0; i < num_items; i++)
    {
        if (items[i].pos > 0)
        {
            sol[items[i].pos - 1] = items[i].size;
        }
    }
    for (int i = 0, total_size = 0; i < num_items; i++)
    {
        total_size += sol[i];
        printf((total_size % bin_size || sol[i] == 0) ? "%d" : "%d ",  sol[i]);
    }
    printf("\n");
}
