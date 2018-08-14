#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define MAX_CARS 1024

typedef struct car_t
{
    int start;
    int end;
} car_t;

static int find_max_rent(int num_reqs, car_t *cars, int *rents);
static void print_rents(int i, int j, int num_reqs, int *rents, car_t *cars);
static int comp(const void *a, const void *b);

int main(void)
{
    int num_reqs = 0;
    car_t cars[MAX_CARS] = { { 0 } };

    scanf("%d", &num_reqs);
    num_reqs += 2;
    for (int i = 1; i < num_reqs - 1; i++)
    {
        scanf("%d", &cars[i].start);        
    }
    for (int i = 1; i < num_reqs - 1; i++)
    {
        scanf("%d", &cars[i].end);        
    }
    // Sentinels
    cars[0].end = 0;
    cars[num_reqs - 1].start = INT_MAX;
    qsort(&cars[1], num_reqs - 2, sizeof(car_t), comp);

    int *rents = (int *)malloc(num_reqs * num_reqs * sizeof(int));
    printf("%d\n", find_max_rent(num_reqs, cars, rents));
    print_rents(0, num_reqs - 1, num_reqs, rents, cars);
    printf("\n");
    free(rents);
    
    return EXIT_SUCCESS;
}

int find_max_rent(int num_reqs, car_t *cars, int *rents)
{
    for (int j = 0; j < num_reqs; j++)
    {
        for (int i = j; i >= 0; i--)
        {
            int max_rent = 0;
            int choice = 0;
            for (int k = i + 1; k < j; k++)
            {
                if (cars[k].start >= cars[i].end && cars[k].end <= cars[j].start)
                {
                    int rent = rents[i * num_reqs + k] + 1 + rents[k * num_reqs + j];
                    if (rent > max_rent)
                    {
                        choice = k;
                        max_rent = rent;
                    }
                }
            }
            rents[i * num_reqs + j] = max_rent;
            // Store the choice in the back end of the array
            rents[j * num_reqs + i] = choice;
        }
    }
    return rents[num_reqs - 1];
}

void print_rents(int i, int j, int num_reqs, int *rents, car_t *cars)
{
    int k = rents[j * num_reqs + i];

    if (k > 0)
    {
        print_rents(i, k, num_reqs, rents, cars);
        printf("(%d, %d) ", cars[k].start, cars[k].end);
        print_rents(k, j, num_reqs, rents, cars);
    }
}

int comp (const void *a, const void *b) 
{
    return ((car_t *)a)->end - ((car_t *)b)->end;
}
