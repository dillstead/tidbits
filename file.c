#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char buf[128] = { 0 };
    FILE *out = fopen("./temp.txt", "w+");
    printf("feof %d\n", feof(out));
    fgets(buf, sizeof(buf), out);
    printf("%s\n", buf);
    printf("feof %d\n", feof(out));
    printf("ftell %ld\n", ftell(out));
    fputs("junk", out);
    printf("feof %d\n", feof(out));
    printf("ftell %ld\n", ftell(out));
    if (fgets(buf, sizeof(buf), out) != NULL)
    {
        printf("feof %d\n", feof(out));
        printf("%s\n", buf);
    }
    else
    {
        printf("NULL\n");
    }
    printf("feof %d\n", feof(out));
    fseek(out, 0, SEEK_CUR);
    printf("feof %d\n", feof(out));
    printf("ftell %ld\n", ftell(out));
    fclose(out);
    return EXIT_SUCCESS;
}
