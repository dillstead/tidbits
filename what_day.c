#include <stdlib.h>
#include <stdio.h>

// Uses https://en.wikipedia.org/wiki/Zeller%27s_congruence
int main(void)
{
    const char *name[] =
    {
        "Saturday",
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday",
        "Sunday"
    };

    int y, m, d = 0;

    while (scanf("%d%d%d", &y, &m, &d) == 3)
    {
        if (m < 3)
        {
            m += 12;
            y--;
        }
        puts(name[(d + 13 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7]);
    }

    return EXIT_SUCCESS;
}
