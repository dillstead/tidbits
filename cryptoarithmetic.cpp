#include <ctype.h>
#include <stdio.h>
#include <gecode/int.hh>
#include <gecode/search.hh>

using namespace Gecode;

typedef struct letter_info_t
{
    bool no_zero;
    int num_coefs;
    int coefs[1024];
} letter_info_t;

static void get_letters(char *line, letter_info_t *letters_info,
        int *num_letters, int *num_coefs);

class CryptoArithmetic : public Space
{
protected:
    IntVarArray letters_;
    char idx_to_char_[26];

public:
    CryptoArithmetic(letter_info_t *letters_info, int num_letters,
            int num_coefs)
        : letters_(*this, num_letters, 0, 9)
    {
        // All letters distinct
        distinct(*this, letters_);

        // Linear equation
        IntArgs coefs(num_coefs);
        IntVarArgs vars(num_coefs);

        for (int i = 0, c = 0, l = 0; i < 26; i++)
        {
            if (letters_info[i].num_coefs > 0)
            {
                idx_to_char_[l] = 'A' + i;
                // No leading zero
                if (letters_info[i].no_zero)
                {
                    rel(*this, letters_[l], IRT_NQ, 0);
                }
                for (int j = 0; j < letters_info[i].num_coefs; j++)
                {
                    coefs[c] = letters_info[i].coefs[j];
                    vars[c++] = letters_[l];
                }
                l++;
            }
        }
        linear(*this, coefs, vars, IRT_EQ, 0);

        // Post branching
        branch(*this, letters_, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
    }

    CryptoArithmetic(bool share, CryptoArithmetic &s) : Space(share, s)
    {
        memcpy(idx_to_char_, s.idx_to_char_, sizeof(idx_to_char_));
        letters_.update(*this, share, s.letters_);
    }

    virtual Space *copy(bool share)
    {
        return new CryptoArithmetic(share, *this);
    }

    void print(void) const
    {
        std::cout << "{";
        for (int i = 0; i < letters_.size(); i++)
        {
            std::cout << "\"" << idx_to_char_[i] << "\"" << "=>" << letters_[i];
            if (i < letters_.size() - 1)
            {
                std::cout << ", ";
            }
        }
        std::cout << "}" << std::endl;
    }
};

int main(int argc, char* argv[])
{
    char line[1024];

    while (fgets(line, 2048, stdin) != NULL)
    {
        int num_letters, num_coefs;
        letter_info_t letters_info[26] = { 0 };

        get_letters(line, letters_info, &num_letters, &num_coefs);
        // Create model and search engine
        CryptoArithmetic model(letters_info, num_letters, num_coefs);
        DFS<CryptoArithmetic> engine(&model);

        // Print first solution
        if (CryptoArithmetic *solution = engine.next())
        {
            solution->print();
            delete solution;
        }
    }
    return 0;
}


void get_letters(char *line, letter_info_t *letters_info,
        int *num_letters, int *num_coefs)
{
    int end = (int)strlen(line);
    int coef = 1;
    bool neg = true;

    *num_letters = 0;
    *num_coefs = 0;

    int c;
    for (int i = end; i >= 0; i--)
    {
        if (isupper(line[i]))
        {
            c = line[i] - 'A';
            letters_info[c].coefs[letters_info[c].num_coefs] =
                    neg ? -coef : coef;
            if (letters_info[c].num_coefs == 0)
            {
                (*num_letters)++;
            }
            coef *= 10;
            (*num_coefs)++;
            letters_info[c].num_coefs++;
        }
        else if (line[i] == '+')
        {
            letters_info[c].no_zero = true;
            coef = 1;
        }
        else if (line[i] == '=')
        {
            letters_info[c].no_zero = true;
            coef = 1;
            neg = false;
        }
    }
    letters_info[c].no_zero = true;
}
