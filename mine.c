#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define NORTH           0x01
#define WEST            0x04
#define SOUTH           0x10
#define EAST            0x40

#define LOOK_F(s, d, w) (s + (-(0x01 & (d)) * (w) - (0x01 & (d) >> 2) + (0x01 & (d) >> 4) * (w) + (0x01 & (d) >> 6)))
#define X(x, y, w) ((x) * (w) + (y))

static uint8_t dir_map[] =
{
    ['N'] = NORTH,
    ['O'] = WEST,
    ['S'] = SOUTH,
    ['E'] = EAST
};

typedef struct minefield_t
{
    int width;
    char *cells;
    int num_cells;
    int exit_pos;
} minefield_t;

typedef struct robot_t
{
    bool start;
    int pos;
} robot_t;

static void read_minefield(const char *file, minefield_t *field, robot_t *robot);
static void read_exit(minefield_t *field);
static void move(minefield_t *field, robot_t *robot);
static void print_minefield(minefield_t *field);
static void fatal_error(const char *msg);

int main(int argc, char **argv)
{
    robot_t robot = { false, 0 };
    minefield_t field = { 0 };

    if (argc != 2)
    {
        printf("Usage: mine <field file>\n");
        exit(EXIT_FAILURE);
    }

    read_minefield(argv[1], &field, &robot);
    move(&field, &robot);
    print_minefield(&field);

    free(field.cells);
    field.cells = NULL;

    return EXIT_SUCCESS;
}

void read_minefield(const char *file, minefield_t *field, robot_t *robot)
{
    struct stat buf;
    if (stat(file, &buf) != 0)
    {
        fatal_error("Unable to get file size");
    }
    if ((field->cells = (char *)malloc(buf.st_size)) == NULL)
    {
        fatal_error("Out of memory");
    }

    FILE *fp;
    if ((fp = fopen(file, "r")) == NULL)
    {
        fatal_error("Unable to open field file");
    }

    bool found_width = false;
    int c;
    while ((c = fgetc(fp)) != EOF)
    {
        if (c == '\n')
        {
            found_width = true;
            continue;
        }
        else if (c == 'M')
        {
            robot->pos = field->num_cells;
        }
        field->cells[field->num_cells++] = c;
        if (!found_width)
        {
            field->width++;
        }
    }
    fclose(fp);
    read_exit(field);
}

void read_exit(minefield_t *field)
{
    int y = field->num_cells / field->width;

    for (int i = 0; i < y; i++)
    {
        if (field->cells[X(i, 0, field->width)] == '0')
        {
            field->exit_pos = X(i, 0, field->width);
        }
        if (field->cells[X(i, field->width - 1, field->width)] == '0')
        {
            field->exit_pos = X(i, field->width - 1, field->width);
        }
    }
    for (int i = 0; i < field->width; i++)
    {
        if (field->cells[X(0, i, field->width)] == '0')
        {
            field->exit_pos = X(0, i, field->width);
        }
        if (field->cells[X(y - 1, i, field->width)] == '0')
        {
            field->exit_pos = X(y - 1, i, field->width);
        }
    }
}

void move(minefield_t *field, robot_t *robot)
{
    print_minefield(field);
    int cmd;
    bool done = false;
    while ((cmd = getchar()) != EOF && !done)
    {
        if (cmd == 'I')
        {
            robot->start = true;
        }
        else if (cmd == '-')
        {
            robot->start = false;
            if (robot->pos == field->exit_pos)
            {
                done = true;
            }
        }
        else if (robot->start && cmd != '\n')
        {
            int pos = LOOK_F(robot->pos, dir_map[cmd], field->width);
            if (field->cells[pos] != '+')
            {
                field->cells[robot->pos] = ' ';
                robot->pos = pos;
                if (field->cells[pos] == '*')
                {
                    field->cells[pos] = 'x';
                    done = true;
                }
                else
                {
                    field->cells[pos] = 'M';
                }
            }
            print_minefield(field);
        }
    }
}

void print_minefield(minefield_t *field)
{
    int y = field->num_cells / field->width;
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < field->width; j++)
        {
            printf("%c", field->cells[X(i, j, field->width)]);
        }
        printf("\n");
    }
}

void fatal_error(const char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}
