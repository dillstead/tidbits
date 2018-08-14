#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd, num, sides;
    unsigned int seed;

    fd = open("/dev/urandom", O_RDONLY);
    read(fd, &seed, sizeof(unsigned int));
    printf("%x\n", seed);
    srand(seed);
    close(fd);

    while (scanf("%dd%d", &num, &sides) == 2)
    {
        int sum = 0;

        for (int i = 0; i < num; i++)
        {
            // Not concerned with skew here
            sum += rand() % sides + 1;
        }
        printf("%d\n", sum);
    }
    return EXIT_SUCCESS;
}
