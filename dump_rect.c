#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

static void draw_line(int x1, int y1, int x2, int y2, int *bmp, int dim);
static void draw_rect(int x, int y, int w, int h, int *bmp, int dim);
static void draw_pixel(int x, int y, int *bmp, int dim);

int main(void)
{
    int dim, x, y, bdim, px, py, cx, cy;

    scanf("%d,[(%d, %d)", &dim, &px, &py);
    int *bmp = (int *)malloc(dim * dim * sizeof(int));

    while (scanf(",(%d,%d)", &cx, &cy) == 2)
    {
        draw_line(px, py, cx, cy, bmp, dim);
        px = cx;
        py = cy;
    }

    scanf("],(%d,%d),%d", &x, &y, &bdim);
    draw_rect(x, y, bdim, bdim, bmp, dim);

    printf("P1\n%d %d\n", dim, dim);
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            printf("%d ", bmp[i * dim + j]);
        }
        printf("\n");
    }

    free(bmp);
    bmp = NULL;

    return EXIT_SUCCESS;
}

#define SWAP_INT(x, y) do { int t = x; x = y; y = t; } while (0)
// See https://www.cs.helsinki.fi/group/goa/mallinnus/lines/bresenh.html
void draw_line(int x1, int y1, int x2, int y2, int *bmp, int dim) 
{
    int x, xe, y, ye, yadj, dx, dy, err;
    bool swap;

    dx = x2 - x1;
    dy = y2 - y1;
    yadj = ((dx > 0 && dy > 0) || (dx < 0 && dy < 0)) ? 1 : -1;
    dx = abs(dx);
    dy = abs(dy);
    if (dy > dx) 
    {
        swap = true;
        SWAP_INT(dx, dy);
        if (y1 < y2) 
        {
            x = y1;
            y = x1;
            xe = y2;
            ye = x2;
        } 
        else 
        {
            x = y2;
            y = x2;
            xe = y1;
            ye = x1;
        }
    } 
    else 
    {
        swap = false;
        if (x1 < x2) 
        {
            x = x1;
            y = y1;
            xe = x2;
            ye = y2;
        } 
        else 
        {
            x = x2;
            y = y2;
            xe = x1;
            ye = y1;
        }
    }
    err = 0;
    while (x != xe) 
    {
        swap ? draw_pixel(y, x, bmp, dim) : draw_pixel(x, y, bmp, dim);
        err += dy;
        if (err * 2 >= dx)
        {
            y += yadj;
            err -= dx;
        }
        x++;
    }
    swap ? draw_pixel(ye, xe, bmp, dim) : draw_pixel(xe, ye, bmp, dim);
}

void draw_rect(int x, int y, int w, int h, int *bmp, int dim) 
{
    draw_line(x, y, x + w, y, bmp, dim);
    draw_line(x, y + h, x + w, y + h, bmp, dim);
    draw_line(x, y, x, y + h, bmp, dim);
    draw_line(x + w, y, x + w, y + h, bmp, dim);
}

void draw_pixel(int x, int y, int *bmp, int dim)
{
    bmp[(dim - 1 - y) * dim + x] = 1;
}
