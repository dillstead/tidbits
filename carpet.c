#include <stdlib.h>
#define __USE_XOPEN2K8
#include <stdio.h>
#include <string.h>

#define MAX_COLORS  128
#define NBRS_DIM    3

static int color_nbrs[MAX_COLORS][9] = { 0 };
static int num_iters = 0;

static int *make_carpet(int iter, int *carpet, int *dim);
static void print_carpet(int *carpet, int dim);

int main(void)
{
    char *line = NULL;
    size_t line_len = 0;
    int num_colors = 0;

    getline(&line, &line_len, stdin);
    sscanf(line, "%d %d", &num_colors, &num_iters);

    for (int i = 0; i < num_colors; i++)
    {
        getline(&line, &line_len, stdin);
        char *colors = line;
        for (int j = 0; j < 9; j++)
        {
            color_nbrs[i][j] = atoi(strtok(colors, " "));
            colors = NULL;
        }
    }
    if (line != NULL)
    {
        free(line);
        line = NULL;
    }

    int dim = 1;
    int *carpet = (int *)malloc(dim * dim * sizeof(int));
    carpet[0] = 0;
    carpet = make_carpet(num_iters, carpet, &dim);
    print_carpet(carpet, dim);
    free(carpet);
    carpet = NULL;

    return EXIT_SUCCESS;
}

int *make_carpet(int iter, int *carpet, int *dim)
{
    if (iter < 1)
    {
        return carpet;
    }
    
    int old_dim = *dim;
    int new_dim = *dim * NBRS_DIM;
    *dim = new_dim;
    int *new_carpet = (int *)malloc(new_dim * new_dim * sizeof(int));
    for (int i = 0; i < old_dim; i++)
    {
        for (int j = 0; j < old_dim; j++)
        {
            int color = carpet[i * old_dim + j];
            for (int k = 0; k < NBRS_DIM; k++)
            {
                for (int l = 0; l < NBRS_DIM; l++)
                {
                    new_carpet[i * NBRS_DIM * new_dim + k * new_dim  + j * NBRS_DIM + l]
                        = color_nbrs[color][k * NBRS_DIM + l];
                }
            }
        }
    }
    free(carpet);
    return make_carpet(--iter, new_carpet, dim);
}

void print_carpet(int *carpet, int dim)
{
    printf("P2\n%d %d\n", dim, dim);
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            printf("%d ", carpet[i * dim + j]);
        }
        printf("\n");
    }
}
