#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_SZ  8
#define RD(b, p)  ((((b)[(p) / 8] >> ((p) % 8)) & 0x1))
#define SET(b, p) (((b)[(p) / 8] = (b)[(p) / 8] | (0x1 << ((p) % 8))))
#define CLR(b, p) (((b)[(p) / 8] = (b)[(p) / 8] & ~(0x1 << ((p) % 8))))

int main(void)
{
    int target;

    while (scanf("%d", &target) == 1)
    {
        int sz = INIT_SZ;
        int cnt[2] = { 0 };
        int i = 0, j = 0, val = 0, diff = 0;
        unsigned char *seq = (unsigned char *)calloc(sz >> 3, sizeof(unsigned char));

        seq[0] = 0x02;
        while (target > 0)
        {
            while (target > 0 && diff < sz - 1)
            {
                unsigned char r = RD(seq, i);

                if (r)
                {
                    if (val)
                    {
                        SET(seq, j);
                    }
                    else
                    {
                        CLR(seq, j);
                    }
                    diff++;
                    j = (j + 1) % sz;
                }
                if (val)
                {
                    SET(seq, j);
                }
                else
                {
                    CLR(seq, j);
                }
                j = (j + 1) % sz;
                i = (i + 1) % sz;
                target--;
                cnt[r] += 1;
                val = !val;
            }
            if (i != target)
            {
                int nsz = sz << 1;
                unsigned char *nseq = (unsigned char *)calloc(nsz >> 3, sizeof(unsigned char));
                int nb = (sz >> 3) - i / 8;

                memcpy(&nseq[0], &seq[i / 8], nb);
                memcpy(&nseq[nb], &seq[0], j / 8 + 1);
                i %= 8;
                j = i + sz - 1;
                free(seq);
                seq = nseq;
                sz = nsz;
            }
        }
        free(seq);
        seq = NULL;
    }
    return EXIT_SUCCESS;
}


