#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>


#define INIT_STEPS      6
#define NUM_DIRS        4
#define NORTH           0x01
#define WEST            0x04
#define SOUTH           0x10
#define EAST            0x40
#define TURN_L(d)       ((d) >> 6 | (d) << 2)
#define TURN_R(d)       ((d) << 6 | (d) >> 2)
#define TURN_A(d)       TURN_L(TURN_L(d))
#define LOOK_F(s, d, w) (s + (-(0x01 & (d)) * (w) - (0x01 & (d) >> 2) + (0x01 & (d) >> 4) * (w) + (0x01 & (d) >> 6)))
#define LOOK_L(s, d, w) (s + (-(0x01 & (d)) + (0x01 & (d) >> 2) * (w) + (0x01 & (d) >> 4) - (0x01 & (d) >> 6) * (w)))
#define LOOK_R(s, d, w) (s + ((0x01 & (d)) - (0x01 & (d) >> 2) * (w) - (0x01 & (d) >> 4) + (0x01 & (d) >> 6) * (w)))

typedef struct maze_t
{
    int width;
    char *cells;
    int num_cells;
    int max_steps;
} maze_t;

typedef struct player_t
{
    int total_steps;
    int steps_left;
    int pos;
    uint8_t dir;
} player_t;

static uint8_t dir_map[] =
{
    ['^'] = NORTH,
    ['<'] = WEST,
    ['v'] = SOUTH,
    ['>'] = EAST
};

static void read_maze(const char *file, maze_t *maze, player_t *player);
static bool find_exit(maze_t *maze, player_t *player);
static void fatal_error(const char *msg);

int main(int argc, char **argv)
{
    player_t player = { 0 };
    maze_t maze = { 0 };

    if (argc != 2)
    {
        printf("Usage: get_out <maze file>\n");
        exit(EXIT_FAILURE);
    }

    read_maze(argv[1], &maze, &player);
    printf("%cay!\n", find_exit(&maze, &player) ? 'Y' : 'N');

    free(maze.cells);
    maze.cells = NULL;

    return EXIT_SUCCESS;
}

void read_maze(const char *file, maze_t *maze, player_t *player)
{
    struct stat buf;
    if (stat(file, &buf) != 0)
    {
        fatal_error("Unable to get file size");
    }
    if ((maze->cells = (char *)malloc(buf.st_size)) == NULL)
    {
        fatal_error("Out of memory");
    }

    FILE *fp;
    if ((fp = fopen(file, "r")) == NULL)
    {
        fatal_error("Unable to open maze file");
    }

    bool found_width = false;
    int c;
    while ((c = fgetc(fp)) != EOF)
    {
        switch (c)
        {
        case '^':
        case '<':
        case 'v':
        case '>':
        {
            player->dir = dir_map[c];
            player->pos = maze->num_cells;
            c = ' ';
            break;
        }
        case '\n':
        {
            found_width = true;
            continue;
        }
        }
        maze->cells[maze->num_cells++] = c;
        if (!found_width)
        {
            ++maze->width;
        }
    }
    maze->max_steps = maze->num_cells * NUM_DIRS;
    player->steps_left = INIT_STEPS;

    fclose(fp);
}

bool find_exit(maze_t *maze, player_t *player)
{
    while (player->total_steps < maze->max_steps
           && maze->cells[player->pos] != 'E')
    {
        if (player->steps_left > 0)
        {
            if (maze->cells[LOOK_F(player->pos, player->dir, maze->width)] != '#')
            {
                player->pos = LOOK_F(player->pos, player->dir, maze->width);
                --(player->steps_left);
                ++(player->total_steps);
            }
            else if (maze->cells[LOOK_R(player->pos, player->dir, maze->width)] != '#')
            {
                player->dir = TURN_R(player->dir);
            }
            else if (maze->cells[LOOK_L(player->pos, player->dir, maze->width)] != '#')
            {
                player->dir = TURN_L(player->dir);
            }
            else
            {
                player->dir = TURN_A(player->dir);
            }
        }
        else
        {
            player->dir = TURN_A(player->dir);
            player->steps_left = INIT_STEPS;
        }
    }

    return player->total_steps < maze->max_steps;
}

void fatal_error(const char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}
