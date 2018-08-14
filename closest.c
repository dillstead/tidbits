#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_NUM_STRS 128
#define MAX_STR_LEN  128

static int calc_dist(const char *str1, const char *str2,
    size_t str_len);

int main(void)
{
    int num_strs;
    size_t str_len;
    char strs[MAX_NUM_STRS][MAX_STR_LEN] = { { 0 } };
    int dists[MAX_NUM_STRS] = { 0 };

    scanf("%d\n", &num_strs);

    for (int i = 0; i < num_strs; i++)
    {
        fgets(strs[i], sizeof(strs[i]), stdin);
    }
    str_len = strlen(strs[0]) - 1;

    for (int i = 0; i < num_strs; i++)
    {
        for (int j = i + 1; j < num_strs; j++)
        {
            int dist = calc_dist(strs[i], strs[j], str_len);
            dists[i] += dist;
            dists[j] += dist;
        }
    }
    
    int j = 0;
    int min_dist = INT_MAX;

    for (int i = 0; i < num_strs; i++)
    {
        if (dists[i] < min_dist)
        {
            min_dist = dists[i];
            j = i;
        }
    }

    printf("%s", strs[j]);
    
    return EXIT_SUCCESS;
}

int calc_dist(const char *str1, const char *str2, size_t str_len)
{
    int dist = 0;

    for (int i = 0; i < str_len; i++)
    {
        if (str1[i] != str2[i])
        {
            dist++;
        }
    }
    
    return dist;
}
