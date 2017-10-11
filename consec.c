#include <stdlib.h>
#include <stdio.h>

static int sum_consec(int *seq, size_t seq_len);

int main(void)
{
    size_t num_seqs = 0;
    size_t seq_len = 0;
    int seqs[1024] = { 0 };

    scanf("%zu %zu", &num_seqs, &seq_len);
    for (size_t i = 0; i < num_seqs * seq_len; i++)
    {
        scanf("%d", &seqs[i]);
    }
    for (size_t i = 0; i < num_seqs; i++)
    {
        printf("%d\n", sum_consec(&seqs[i * seq_len], seq_len));        
    }

    return EXIT_SUCCESS;
}

int sum_consec(int *seq, size_t seq_len)
{
    int pos[100] = {[0 ... 99] = -1 };
    int sum = 0;

    for (size_t i = 0; i < seq_len; i++)
    {
        pos[seq[i]] = i;
    }
    for (size_t i = 0; i < 99; i++)
    {
        if (pos[i] != -1 && pos[i + 1] != -1)
        {
            sum += abs(pos[i] - pos[i + 1]);
        }
    }
    return sum;
}
