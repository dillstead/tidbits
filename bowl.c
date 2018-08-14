#include <stdio.h>
#include <stdlib.h>

static char disp[][11][3] =
{
    {
        "--", "-1", "-2", "-3", "-4",
        "-5", "-6", "-7", "-8", "-9",
        "-/"
    },
    {
        "1-", "11", "12", "13", "14",
        "15", "16", "17", "18", "1/"
    },
    {
        "2-", "21", "22", "23", "24",
        "25", "26", "27", "2/"
    },
    {
        "3-", "31", "32", "33", "34",
        "35", "36", "3/"
    },
    {
        "4-", "41", "42", "43", "44",
        "45", "4/"
    },
    {
        "5-", "51", "52", "53", "54",
        "5/"
    },
    {
        "6-", "61", "62", "63", "6/"
    },
    {
        "7-", "71", "72", "7/"
    },
    {
        "8-", "81", "8/"
    },
    {
        "9-", "9/"
    }
};

int main(void)
{
    int roll = -1, prev_roll = -1;
    int frame = 1;
    
    while (scanf("%d", &roll) == 1)
    {
        if (roll == 10 && prev_roll != 0)
        {
            printf(frame < 10 ? "X " : "X");
            prev_roll = -1;
            frame++;
        }
        else if (prev_roll != -1)
        {
            printf(frame < 10 ? "%s " : "%s", disp[prev_roll][roll]);
            prev_roll = -1;
            frame++;
        }
        else
        {
            prev_roll = roll;
        }
    }
    if (prev_roll != -1)
    {
        printf("%d", roll);
    }
    printf("\n");
    return EXIT_SUCCESS;
}
