#include <stdlib.h>
#define __USE_XOPEN2K8
#include <stdio.h>
#include <string.h>

#define MAX_HEIGHTS 128

static void plan_route(int heights[], size_t num_heights);

int main(void)
{
    char *line = NULL;
    size_t line_len = 0;

    while (getline(&line, &line_len, stdin) != -1) 
    {
        line[strcspn(line, "\n")] = '\0';
        const char *height = strtok(line, " ");
        int heights[MAX_HEIGHTS] = { 0 };
        size_t num_heights = 0;
        while (height != NULL)
        {
            heights[num_heights++] = atoi(height);
            height = strtok(NULL, " ");
        }
        plan_route(heights, num_heights);
    }
    if (line != NULL)
    {
        free(line);
        line = NULL;
    }
    return EXIT_SUCCESS;
}

void plan_route(int heights[], size_t num_heights)
{
    int route_lens[MAX_HEIGHTS] = { 0 };
    int max_route_len= 0;
    size_t next_peaks[MAX_HEIGHTS] = { 0 };
    size_t start_peak = 0;

    for (int i = num_heights - 1; i >= 0; i--)
    {
        int route_len = 1;
        size_t next_peak = 0;

        for (int j = i + 1; j < num_heights; j++)
        {
            if (heights[i] < heights[j]
                && route_lens[j] >= route_len)
            {
                route_len = route_lens[j] + 1;
                next_peak = j;
            }
        }
        route_lens[i] = route_len;
        next_peaks[i] = next_peak;
        if (route_len >= max_route_len)
        {
            max_route_len = route_len;
            start_peak = i;
        }
    }
    do
    {
        printf("%d ", heights[start_peak]);        
        start_peak = next_peaks[start_peak];
    } while (start_peak != 0);
    printf("\n");
}
