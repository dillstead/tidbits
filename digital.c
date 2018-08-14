#include <stdlib.h>
#include <stdio.h>

static int imap[] =
{
    [' '] = 0,
    ['_'] = 1,
    ['|'] = 2
};

int main(void)
{
    static int disp[3][3][3][3][3][3][3][3][3];
    int input[9][3][3];

    disp[imap[' ']][imap['_']][imap[' ']][imap['|']][imap[' ']][imap['|']][imap[' ']][imap['_']][imap['|']] = 0;
    disp[imap[' ']][imap[' ']][imap[' ']][imap[' ']][imap[' ']][imap['|']][imap[' ']][imap[' ']][imap['|']] = 1;
    disp[imap[' ']][imap['_']][imap[' ']][imap[' ']][imap['_']][imap['|']][imap['|']][imap['_']][imap[' ']] = 2;
    disp[imap[' ']][imap['_']][imap[' ']][imap[' ']][imap['_']][imap['|']][imap[' ']][imap['_']][imap['|']] = 3;
    disp[imap[' ']][imap[' ']][imap[' ']][imap['|']][imap['_']][imap['|']][imap[' ']][imap[' ']][imap['|']] = 4;
    disp[imap[' ']][imap['_']][imap[' ']][imap['|']][imap['_']][imap[' ']][imap[' ']][imap['_']][imap['|']] = 5;
    disp[imap[' ']][imap['_']][imap[' ']][imap['|']][imap['_']][imap[' ']][imap['|']][imap['_']][imap['|']] = 6;
    disp[imap[' ']][imap['_']][imap[' ']][imap[' ']][imap[' ']][imap['|']][imap[' ']][imap[' ']][imap['|']] = 7;
    disp[imap[' ']][imap['_']][imap[' ']][imap['|']][imap['_']][imap['|']][imap['|']][imap['_']][imap['|']] = 8;
    disp[imap[' ']][imap['_']][imap[' ']][imap['|']][imap['_']][imap['|']][imap[' ']][imap['_']][imap['|']] = 9;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                input[j][i][k] = imap[getchar()];
            }
        }
        getchar(); // \n or EOF
    }
    for (int i = 0; i < 9; i++)
    {
        printf("%d", disp[input[i][0][0]][input[i][0][1]][input[i][0][2]][input[i][1][0]][input[i][1][1]][input[i][1][2]][input[i][2][0]][input[i][2][1]][input[i][2][2]]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}
