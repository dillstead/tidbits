#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0
#define CTOI(c) ((c) - '0')

static const char *thousands[] =
{
    "\0",
    "\0",
    " thousand"
};

static const char *ones_cap[] = 
{
    "\0\0\0\0",
    " o\0O",
    " t\0T",
    " t\0T",
    " f\0F",
    " f\0F",
    " s\0S",
    " s\0S",
    " e\0E",
    " n\0N",
    " t\0T",
    " e\0E",
    " t\0T",
    " t\0T",
    " f\0F",
    " f\0F",
    " s\0S",
    " s\0S",
    " e\0E",
    " n\0N"
};

static const char *ones[] = 
{
    "\0",
    "ne",
    "wo",
    "hree",
    "our",
    "ive",
    "ix",
    "even",
    "ight",
    "ine",
    "en",
    "leven",
    "welve",
    "hirteen",
    "ourteen",
    "ifteen",
    "ixteen",
    "eventeen",
    "ighteen",
    "ineteen"
};

static const char *tens_cap[] =
{
    "\0\0\0\0",
    "\0\0\0\0",
    " t\0T",
    " t\0T",
    " f\0F",
    " f\0F",
    " s\0S",
    " s\0S",
    " e\0E",
    " n\0N"
};

static const char *tens[] = 
{
    "\0",
    "\0",
    "wenty",
    "hirty",
    "orty",
    "ifty",
    "ixty",
    "eventy",
    "ighty",
    "inety"
};

static void print_check(const char *amt);
static void print_dollars(const char *amt, size_t len_amt);
static void print_cents(const char *amt, size_t len_amt);
static int val_hundred(const char *amt, size_t len_amt);
static int print_hundred(const char *amt, size_t len_amt, int val, size_t mag, int cap);
static void print_tens(const char *amt, int cap);
static void print_ones(const char *amt, int cap);

int main(int arc, char **argv)
{
    print_check("400120.0");
    print_check("400120.00");
    print_check("400120");
    print_check("333.88");
    print_check("742388.15");
    print_check("919616.12");
    print_check("12.11");
    print_check("2.0");

    return 0;
}

void print_check(const char *amt)
{
    const char *dec_pos = strchr(amt, '.');
    size_t len_amt = strlen(amt);
    size_t len_dollars = (dec_pos != NULL) ? dec_pos - amt : len_amt;
    size_t len_cents = (dec_pos != NULL) ? len_amt - len_dollars - 1 : 0;

    print_dollars(amt, len_dollars);
    print_cents(amt + len_dollars + 1, len_cents);
}

void print_dollars(const char *amt, size_t len_amt)
{
#if DEBUG
    printf("print_dollars %s, %d\n", amt, len_amt);
#endif
    size_t num_hundreds = (len_amt + 2) / 3;
    size_t len_first_hundred = len_amt % 3;
    int val = 0;
    int non_zero = 0;

    if (num_hundreds && !len_first_hundred)
    {
        len_first_hundred = 3;
    }
    
    val = val_hundred(amt, len_first_hundred);
    print_hundred(amt, len_first_hundred, val, num_hundreds, 3);
    non_zero += val;

    int i = num_hundreds - 1;
    for (amt += len_first_hundred; i > 0; amt += 3, i--)
    {
        if (val > 0)
        {
            printf(",");
        }
        val = val_hundred(amt, 3);
        print_hundred(amt, 3, val, i, 0);
        non_zero += val;
    }

    if (!non_zero)
    {
        printf(" Zero");
    }
    if (num_hundreds == 1 && val == 1)
    {
        printf(" dollar");
    }
    else
    {
        printf(" dollars");
    }
}

void print_cents(const char *amt, size_t len_amt)
{
#if DEBUG
    printf("print_cents %s, %d\n", amt, len_amt);
#endif
    int val = 0;

    printf(" and");
    if (len_amt > 0)
    {
        val = val_hundred(amt, len_amt);
        print_hundred(amt, len_amt, val, 1, 0);
    }
    if (val == 0)
    {
        printf(" zero");
    }
    val == 1 ? printf(" cent.\n") : printf(" cents.\n");
}

int val_hundred(const char *amt, size_t len_amt)
{
    int val = 0;
    int i = 0;

    for (; i < len_amt; i++)
    {
        val = 10 * val + CTOI(*amt++);
    }

#if DEBUG
    printf("val_hundred %s, %d, %d\n", amt, len_amt, val);
#endif
    return val;
}

int print_hundred(const char *amt, size_t len_amt, int val, size_t mag, int cap)
{
#if DEBUG
    printf("print_hundred %s, %d, %d, %d, %d\n", amt, len_amt, val, mag, cap);
#endif
    if (len_amt == 3)
    {
        print_ones(amt, cap);
        if (*amt++ != '0')
        {
            printf(" hundred");
        }
        print_tens(amt, 0);
    }
    else if (len_amt == 2)
    {
        print_tens(amt, cap);
    }
    else if (len_amt == 1)
    {
        print_ones(amt, cap);
    }

    if (val > 0)
    {
        printf(thousands[mag]);
    }

    return val;
}

void print_tens(const char *amt, int cap)
{
#if DEBUG
    printf("print_tens %s, %d\n", amt, cap);
#endif
    if (*amt == '1')
    {
        int i = 10 * CTOI(*amt) + CTOI(*(amt + 1));
        printf("%s%s", ones_cap[i] + cap, ones[i]);
    }
    else
    {
        int i = CTOI(*amt++);
        printf("%s%s", tens_cap[i] + cap, tens[i]);
        print_ones(amt, cap);
    }
}

void print_ones(const char *amt, int cap)
{
#if DEBUG
    printf("print_ones %s, %d\n", amt, cap);
#endif
    int i = CTOI(*amt);

    printf("%s%s", ones_cap[i] + cap, ones[i]);
}

