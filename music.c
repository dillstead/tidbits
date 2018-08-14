#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct note_t
{
    char name[10];
    float st;
    float dur;
} note_t;

static int mozart_tbl[16][11] =
{
    {96, 32, 69, 40, 148, 104, 152, 119, 98, 3, 54},
    {22, 6, 95,17, 74, 157, 60, 84, 142, 87, 130},
    {141, 128, 158, 113, 163, 27, 171, 114, 42, 165, 10},
    {41, 63, 13, 85, 45, 167, 53, 50, 156, 61, 103},
    {105, 146, 153, 161, 80, 154, 99, 140, 75, 135, 28},
    {122, 46, 55, 2, 97, 68, 133, 86, 129, 47, 37},
    {11, 134, 110, 159, 36, 118, 21, 169, 62, 147, 106},
    {30, 81, 24, 100, 107, 91, 127, 94, 123, 33, 5},
    {70, 117, 66, 90, 25, 138, 16, 120, 65, 102, 35},
    {121, 39, 136, 176, 143, 71, 155, 88, 77, 4, 20},
    {26, 126, 15, 7, 64, 150, 57, 48, 19, 31, 108},
    {9, 56, 132, 34, 125, 29, 175, 166, 82, 164, 92},
    {112, 174, 73, 67, 76, 101, 43, 51, 137, 144, 12},
    {49, 18, 58, 160, 136, 162, 168, 115, 38, 59, 124},
    {109, 116, 145, 52, 1, 23, 89, 72, 149, 173, 44},
    {14, 83, 79, 170, 93, 151, 172, 111, 8, 78, 131}
};

int main(void)
{
    note_t comp[578 * 10];
    int msr_map[176];

    scanf("%s%f%f", comp[0].name, &comp[0].st, &comp[0].dur);
    msr_map[0] = 0;
    int i = 1, m = 1;
    while (scanf("%s%f%f", comp[i].name, &comp[i].st, &comp[i].dur) == 3)
    {
        if ((int)(comp[i].st) % 3 == 0 && (int)(comp[i - 1].st) % 3 == 2)
        {
            msr_map[m++] = i;
        }
        i++;
    }

    int num_notes = i;
    srand(time(NULL));
    for (i = 0; i < 16; i++)
    {
        int r = mozart_tbl[i][rand() % 11] - 1;
        int j = msr_map[r];
        float base = comp[j].st;

        while (j < num_notes && j != msr_map[r + 1])
        {
            printf("%s %g %g\n",  comp[j].name, comp[j].st - base + (i * 3), comp[j].dur);
            j++;
        }

    }

    return EXIT_SUCCESS;
}
