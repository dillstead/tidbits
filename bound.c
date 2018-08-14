#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

typedef struct rect_t
{
    int x1;
    int x2;
    int y1;
    int y2;
} rect_t;

#define MAX_INT(a,b) (((a) > (b)) ? (a) : (b))
#define MIN_INT(a,b) (((a) < (b)) ? (a) : (b))
#define SWAP_INT(x, y) do { int t = x; x = y; y = t; } while (0)

static void square(int dim, rect_t *rect);
static void expand(int dim, int *bl, int *tr, int pbl, int ptr);
static void pad(int dim, rect_t *rect, rect_t *sq);
static int calc_pad(int p, int db, int dbl, int dtr, int *pbl, int *ptr);

int main(void)
{
    rect_t rect = { INT_MAX, 0, INT_MAX, 0 };
    int dim, x, y;
    
    scanf("%d, [", &dim);
    printf("%d,[", dim);

    bool f = true;

    while (scanf("(%d, %d),", &x, &y) == 2)
    {
        if (!f)
        {
            printf(",");
        }
        printf("(%d,%d)", x,y);
        rect.x1 = MIN_INT(rect.x1, x);
        rect.x2 = MAX_INT(rect.x2, x);
        rect.y1 = MIN_INT(rect.y1, y);
        rect.y2 = MAX_INT(rect.y2, y);
        if (f)
        {
            f = false;
        }
    }

    rect_t sq = rect;

    square(dim, &sq);
    pad(dim, &rect, &sq);
    printf("],(%d,%d),%d\n", sq.x1, sq.y1, sq.x2 - sq.x1);

    return EXIT_SUCCESS;
}

void square(int dim, rect_t *rect)
{
    fprintf(stderr, "square\n");
    fprintf(stderr, "%d %d %d %d\n", rect->x1, rect->x2, rect->y1, rect->y2);


    int dx = rect->x2 - rect->x1;
    int dy = rect->y2 - rect->y1;
    int p = abs(dx - dy) / 2;
    int p1 = abs(dx - dy) % 2;

    fprintf(stderr, "%d %d %d %d\n", dx, dy, p, p1);
    
    if (dx > dy)
    {
        expand(dim, &rect->y1, &rect->y2, p + p1, p);
    }
    else
    {
        expand(dim, &rect->x1, &rect->x2, p + p1, p);
    }
}

void expand(int dim, int *bl, int *tr, int pbl, int ptr)
{
    fprintf(stderr, "expand\n");
    fprintf(stderr, "%d %d %d %d %d\n", dim, *bl, *tr, pbl, ptr);

    *bl -= pbl;
    if (*bl < 0)
    {
        *tr -= *bl;
        *bl = 0;
    }
    fprintf(stderr, "%d %d\n", *bl, *tr);

    *tr += ptr;
    if (*tr > dim - 1)
    {
        *bl -= (*tr - dim - 1);
        *tr = dim - 1;
    }
    fprintf(stderr, "%d %d\n", *bl, *tr);
}

void pad(int dim, rect_t *rect, rect_t *sq)
{
    int p1, p2;
    
    fprintf(stderr, "pad\n");
    fprintf(stderr, "%d %d %d %d, %d %d %d %d\n", rect->x1, rect->x2, rect->y1, rect->y2, sq->x1, sq->x2, sq->y1, sq->y2);

    sq->x1 -= calc_pad(sq->x1, rect->x1 - sq->x1, rect->y1 - sq->y1, sq->y2 - rect->y2, &p1, &p2);
    expand(dim, &sq->y1, &sq->y2, p1, p2);
    sq->x2 += calc_pad(dim - 1 - sq->x2, sq->x2 - rect->x2, rect->y1 - sq->y1, sq->y2 - rect->y2, &p1, &p2);
    expand(dim, &sq->y1, &sq->y2, p1, p2);
    sq->y1 -= calc_pad(sq->y1, rect->y1 - sq->y1, rect->x1 - sq->x1, sq->x2 - rect->x2, &p1, &p2);
    expand(dim, &sq->x1, &sq->x2, p1, p2);
    sq->y2 += calc_pad(dim - 1 - sq->y2, sq->y2 - rect->y2, rect->x1 - sq->x1, sq->x2 - rect->x2, &p1, &p2);
    expand(dim, &sq->x1, &sq->x2, p1, p2);
}

int calc_pad(int dd, int ds, int dbl, int dtr, int *pbl, int *ptr)
{
    fprintf(stderr, "calc_pad\n");
    fprintf(stderr, "%d %d %d %d\n", dd, ds, dbl, dtr);

    int m = 0;
    if (ds < 30)
    {
        m = MIN_INT(dd, 30 - ds);
    }
    fprintf(stderr, "%d\n", m);

    *pbl = m / 2;
    *ptr = *pbl;
    fprintf(stderr, "%d %d\n", *pbl, *ptr);
    if (dbl > dtr)
    {
        *pbl += m % 2;
    }
    else
    {
        *ptr += m % 2;
    }
    fprintf(stderr, "%d %d\n", *pbl, *ptr);

    return m;
}

