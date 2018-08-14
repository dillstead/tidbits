#define _XOPEN_SOURCE 700
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define  MAX_LINE_LEN    1024
#define  MAX_MOVES       1024
#define  NUM_FACES       6
#define  FACE_SIZE       9

static void parse_move(const char *tok, int *rots, int **face);
static void do_move(int *cube, int rots, int *face);
static int *make_comp(int *comp);

int main(void)
{
    char line[MAX_LINE_LEN] = { 0 };
    static int init[NUM_FACES * FACE_SIZE] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53 };

    while (fgets(line, MAX_LINE_LEN, stdin) != NULL)
    {
        int cube[NUM_FACES * FACE_SIZE] = { 0 };
        memcpy(cube, init, sizeof(init));
        const char *tok = strtok(line, " \n"); 

        while (tok != NULL)
        {
            int rots;
            int *face;
            parse_move(tok, &rots, &face);
            do_move(cube, rots, face);
            tok = strtok(NULL, " ");
        }

`        int *comp = make_comp(cube);
        int reps = 1;

        do 
        {
            do_move(cube, 1, comp);
            ++reps;
        } while (memcmp(cube, init, sizeof(init)));
        printf("%d\n", reps);
    }

    return EXIT_SUCCESS;
}

void parse_move(const char *tok, int *rots, int **face)
{
    *rots = 1;
    if (strlen(tok) > 1)
    {
        *rots = 2;
        if (tok[1] == '\'')
        {
            *rots = 3;
        }
    }
    switch (tok[0])
    {
    case 'F':
    {
        static int front[NUM_FACES * FACE_SIZE] = { 6, 3, 0, 7, 4, 1, 8, 5, 2, 42, 10, 11, 43, 13, 14, 44, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 45, 30, 31, 46, 33, 34, 47, 36, 37, 38, 39, 40, 41, 35, 32, 29, 15, 12, 9, 48, 49, 50, 51, 52, 53 };
        *face = front;
        break;
    }
    case 'B':
    {
        static int back[NUM_FACES * FACE_SIZE] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 53, 12, 13, 52, 15, 16, 51, 24, 21, 18, 25, 22, 19, 26, 23, 20, 38, 28, 29, 37, 31, 32, 36, 34, 35, 11, 14, 17, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 27, 30, 33 };
        *face = back;
        break;
    }
    case 'L':
    {
        static int left[NUM_FACES * FACE_SIZE] = { 36, 1, 2, 39, 4, 5, 42, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 51, 21, 22, 48, 24, 25, 45, 33, 30, 27, 34, 31, 28, 35, 32, 29, 26, 37, 38, 23, 40, 41, 20, 43, 44, 0, 46, 47, 3, 49, 50, 6, 52, 53 };
        *face = left;
        break;
    }
    case 'R':
    {
        static int right[NUM_FACES * FACE_SIZE] = { 0, 1, 47, 3, 4, 50, 6, 7, 53, 15, 12, 9, 16, 13, 10, 17, 14, 11, 44, 19, 20, 41, 22, 23, 38, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 2, 39, 40, 5, 42, 43, 8, 45, 46, 24, 48, 49, 21, 51, 52, 18 };
        *face = right;
        break;
    }
    case 'U':
    {
        static int up[NUM_FACES * FACE_SIZE] = { 9, 10, 11, 3, 4, 5, 6, 7, 8, 18, 19, 20, 12, 13, 14, 15, 16, 17, 27, 28, 29, 21, 22, 23, 24, 25, 26, 0, 1, 2, 30, 31, 32, 33, 34, 35, 42, 39, 36, 43, 40, 37, 44, 41, 38, 45, 46, 47, 48, 49, 50, 51, 52, 53 };
        *face = up;
        break;
    }
    case 'D':
    {
        static int down[NUM_FACES * FACE_SIZE] = { 0, 1, 2, 3, 4, 5, 33, 34, 35, 9, 10, 11, 12, 13, 14, 6, 7, 8, 18, 19, 20, 21, 22, 23, 15, 16, 17, 27, 28, 29, 30, 31, 32, 24, 25, 26, 36, 37, 38, 39, 40, 41, 42, 43, 44, 51, 48, 45, 52, 49, 46, 53, 50, 47 };
        *face = down;
        break;
    }
    }
}

void do_move(int *cube, int rots, int *face)
{
    int temp[NUM_FACES * FACE_SIZE] = { 0 };
    for (int i = 0; i < rots; ++i)
    {
        for (int j = 0; j < NUM_FACES * FACE_SIZE; ++j)
        {
            temp[face[j]] = cube[j];
        }
        memcpy(cube, temp, sizeof(temp));
    }
}

int *make_comp(int *cube)
{
    static int comp[NUM_FACES * FACE_SIZE];
    
    memset(comp, 0, sizeof(comp));
    for (int i = 0; i < NUM_FACES * FACE_SIZE; i++)
    {
        comp[cube[i]] = i;
    }
    return comp;
}
