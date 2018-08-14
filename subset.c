#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

static void min_subset(int coins[], int num_coins, int target_sum, 
                       int sum, int set_pos, bool set[], int set_num_coins,
                       bool sol[], int *sol_num_coins, int *sol_set_pos);
int main(void)
{
    int coins[16];    
    int num_coins = 0;
    int target_sum;
    bool set[16];
    bool sol[16];
    int sol_num_coins = INT_MAX;
    int sol_set_pos;

    scanf("Input: %d", &target_sum);
    while (scanf("%d", &coins[num_coins++]) == 1);
    
    min_subset(coins, num_coins, target_sum, 0, 0, set, 0,
               sol, &sol_num_coins, &sol_set_pos);
    if (sol_num_coins < INT_MAX)
    {
        for (int i = 0; i < sol_set_pos; i++)
        {
            if (sol[i])
            {
                printf("%d ", coins[i]);
            }
        }
        printf("\n");
    }
    else
    {
        printf("No solution\n");
    }

    return EXIT_SUCCESS;
}

void min_subset(int coins[], int num_coins, int target_sum, 
                int sum, int set_pos, bool set[], int set_num_coins,
                bool sol[], int *sol_num_coins, int *sol_set_pos)
{
    if (set_num_coins >= *sol_num_coins ||
        set_pos >= num_coins)
    {
        return;
    }
    if (sum == target_sum)
    {
        *sol_num_coins = set_num_coins;
        *sol_set_pos = set_pos;
        memcpy(sol, set, sizeof(bool) * 16);
        return;
    }
    set[set_pos] = true;
    min_subset(coins, num_coins, target_sum, sum + coins[set_pos],
        set_pos + 1, set, set_num_coins + 1, sol, sol_num_coins,
        sol_set_pos);
    set[set_pos] = false;
    min_subset(coins, num_coins, target_sum, sum,
        set_pos + 1, set, set_num_coins, sol, sol_num_coins,
        sol_set_pos);
}
