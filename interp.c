#include <stdlib.h>
#include <stdio.h>
#include <tgmath.h>
#include <string.h>

#define MAX_NAME_SZ  128
#define MAX_TOKS     1024
#define TRUE         1
#define FALSE        0
#define DEBUG        0

typedef enum tok_type_t
{
    NONE = 0,
    VAL,
    VAR,
    OP
} tok_type_t;

typedef union tok_val_t
{
    float fval;
    int ival;
} tok_val_t;

typedef struct tok_t
{
    tok_type_t type;
    tok_val_t val;
    char name[MAX_NAME_SZ];
} tok_t;

typedef enum op_assoc
{
    LEFT_ASSOC = 0,
    RIGHT_ASSOC
} op_assoc;

typedef struct op_info_t
{
    int prec;
    op_assoc assoc;
} op_info_t;

typedef struct stack_t
{
    size_t pos;
    tok_t toks[MAX_TOKS];
} stack_t;

static op_info_t op_tbl[] =
{
    ['^'] = {4, RIGHT_ASSOC},
    ['*'] = {3, LEFT_ASSOC},
    ['/'] = {3, LEFT_ASSOC},
    ['+'] = {2, LEFT_ASSOC},
    ['-'] = {2, LEFT_ASSOC},
    ['='] = {1, RIGHT_ASSOC},
    ['('] = {0, RIGHT_ASSOC}
};

static tok_t var_tbl[MAX_TOKS] = { 0 };
static size_t num_vars = 0;

static void infix_to_postfix(const char *line, tok_t output[]);
static tok_t eval_postfix(tok_t input[]);
static void update_var(tok_t *tok);
static tok_t lookup_var(const char *name, size_t *idx);
static void push_stack(stack_t *stack, tok_t *tok);
static tok_t pop_stack(stack_t *stack, int *is_empty);
static tok_t peek_stack(stack_t *stack, int *is_empty);
static int get_tok(const char **ppos, tok_t *tok);
static void fatal_error(const char *msg);

static void print_stack(stack_t *stack);
static void print_toks(tok_t toks[]);
static void print_tok(tok_t *tok);

int main(void)
{
    tok_t toks[MAX_TOKS] = { 0 };
    char *line = NULL;
    size_t line_len = 0;

    while (getline(&line, &line_len, stdin) != -1) 
    {
        line[strcspn(line, "\n")] = '\0';
        infix_to_postfix(line, toks);
        tok_t res = eval_postfix(toks);
        printf("%g\n", res.val.fval);
        print_tok(&res);
    }
    if (line != NULL)
    {
        free(line);
        line = NULL;
    }

    return EXIT_SUCCESS;
}

void infix_to_postfix(const char *line, tok_t output[])
{
    tok_t tok = { 0 };
    tok_t top = { 0 };
    stack_t op_stack = { 0 };
    const char *line_pos = line;
    size_t output_pos = 0;
    int is_empty = FALSE;

    memset(output, 0, sizeof(tok_t) * MAX_TOKS);
    while (get_tok((const char **) &line_pos, &tok))
    {
        print_tok(&tok);
        switch (tok.type)
        {
        case VAR:
        case VAL:
        {
            output[output_pos++] = tok;
            break;
        }
        case OP:
        {
            if (tok.val.ival == '(')
            {
                push_stack(&op_stack, &tok);
            }
            else if (tok.val.ival == ')')
            {
                is_empty = FALSE;
                top = pop_stack(&op_stack, &is_empty);
                while (top.val.ival != '(')
                {
                    if (is_empty)
                    {
                        fatal_error("Missing '('");
                    }
                    output[output_pos++] = top;
                    top = pop_stack(&op_stack, &is_empty);
                }
            }
            else
            {
                top = peek_stack(&op_stack, &is_empty);
                while (!is_empty && (op_tbl[top.val.ival].prec > op_tbl[tok.val.ival].prec
                                     || (op_tbl[top.val.ival].prec == op_tbl[tok.val.ival].prec
                                         && op_tbl[top.val.ival].assoc == LEFT_ASSOC)))
                {
                    top = pop_stack(&op_stack, &is_empty);
                    output[output_pos++] = top;        
                    top = peek_stack(&op_stack, &is_empty);            
                }
                push_stack(&op_stack, &tok);
            }
            break;
        }
        default:
        {
            fatal_error("Unknown token type");
        }
        }
        print_stack(&op_stack);
        print_toks(output);
    }
    top = pop_stack(&op_stack, &is_empty);
    while (!is_empty)
    {
        if (top.val.ival == '(')
        {
            fatal_error("Mismatched parenthesis");
        }
        output[output_pos++] = top;
        top = pop_stack(&op_stack, &is_empty);
    }
    print_stack(&op_stack);
    print_toks(output);
}

tok_t eval_postfix(tok_t input[])
{
    stack_t eval_stack = { 0 };
    tok_t rtok = { 0 };
    tok_t ltok = { 0 };
    int is_empty = FALSE;
    int i = 0;

    while (input[i].type != NONE)
    {
        switch (input[i].type)
        {
        case VAR:
        case VAL:
        {
            push_stack(&eval_stack, &input[i]);
            break;
        }
        case OP:
        {
            tok_t res = { VAL, 0, { 0 } };

            rtok = pop_stack(&eval_stack, &is_empty);
            if (is_empty)
            {
                fatal_error("No right value");
            }
            ltok = pop_stack(&eval_stack, &is_empty);
            if (is_empty)
            {
                fatal_error("No left value");
            }
            if (rtok.type == VAR)
            {
                rtok = lookup_var(rtok.name, NULL);
            }
            if (ltok.type == VAR && input[i].val.ival != '=')
            {
                ltok = lookup_var(ltok.name, NULL);
            }
            if (rtok.type == NONE || ltok.type == NONE)
            {
                fatal_error("Undefined variable");
            }
            switch (input[i].val.ival)
            {
            case '^':
            {
                res.val.fval = pow(ltok.val.fval, rtok.val.fval);
                break;
            }
            case '*':
            {
                res.val.fval = ltok.val.fval * rtok.val.fval;
                break;
            }
            case '/':
            {
                res.val.fval = ltok.val.fval / rtok.val.fval;
                break;
            }
            case '+':
            {
                res.val.fval = ltok.val.fval + rtok.val.fval;
                break;
            }
            case '-':
            {
                res.val.fval = ltok.val.fval - rtok.val.fval;
                break;
            }
            case '=':
            {
                if (ltok.type != VAR)
                {
                    fatal_error("Invalid lvalue");
                }
                res.val.fval = ltok.val.fval = rtok.val.fval;
                update_var(&ltok);
                break;
            }
            default:
            {
                fatal_error("Unknown operator");
            }
            }
            push_stack(&eval_stack, &res);
            print_stack(&eval_stack);
            break;
        }
        default:
        {
            fatal_error("Unknown token type");
        }
        }
        print_stack(&eval_stack);
        i++;
    }
    return pop_stack(&eval_stack, &is_empty);
}

void update_var(tok_t *tok)
{
    size_t idx = 0;
    tok_t exist = lookup_var(tok->name, &idx);

    if (exist.type != NONE)
    {
        var_tbl[idx] = *tok;
    }
    else
    {
        num_vars < MAX_TOKS ? var_tbl[num_vars++] = *tok
            : fatal_error("Table overflow");
    }
}
/*
9 + 10
(2 * 5 + 1) / 10
x =  1 / 2
y = x * 2
(x + 2) * (y * (5 - 100))
z = 5*-3.14
2.6^(2 + 3/2) * (2-z)
*/

/*
19
1.1
0.5
1
-237.5
-15.7
501.625937332*/

tok_t lookup_var(const char *name, size_t *idx)
{
    tok_t found = { 0 };
    int i = 0;
    
    while (i < num_vars)
    {
        if (!strncmp(var_tbl[i].name, name, MAX_NAME_SZ))
        {
            found = var_tbl[i];
            if (idx != NULL)
            {
                *idx = i;
            }
            break;
        }
        i++;
    }
    return found;
}

void push_stack(stack_t *stack, tok_t *tok)
{
    if (stack->pos >= MAX_TOKS)
    {
        fatal_error("Stack overflow");
    }
    stack->toks[stack->pos++] = *tok;
}

tok_t pop_stack(stack_t *stack, int *is_empty)
{
    if (stack->pos > 0)
    {
        *is_empty = FALSE;
        return stack->toks[--stack->pos];
    }
    else 
    {
        tok_t empty = { 0 };
        *is_empty = TRUE;
        return empty;
    }
}

tok_t peek_stack(stack_t *stack, int *is_empty)
{
    if (stack->pos > 0)
    {
        *is_empty = FALSE;
        return stack->toks[stack->pos - 1];
    }
    else 
    {
        tok_t empty = { 0 };
        *is_empty = TRUE;
        return empty;
    }
}

int get_tok(const char **ppos, tok_t *tok)
{
    int done = FALSE;
    int found_tok = FALSE;
    const char *pos = *ppos;
    char *name_pos = tok->name;
    static tok_t prev_tok = { 0 };

    memset(tok, 0, sizeof(tok_t));
    while (!done && *pos != '\0')
    {
        if ((*pos == '-' && (tok->type != NONE || prev_tok.type == VAL || prev_tok.type == VAR || prev_tok.val.ival == ')'))
            || *pos == '+' || *pos == '*' || *pos == '/' || *pos == '^' || *pos == '(' || *pos == ')' || *pos == '=')
        {
            if (tok->type != NONE)
            {
                /* Don't consume */
                pos--;
            }
            else
            {
                tok->type = OP;
                tok->val.ival = *pos;
                found_tok = TRUE;
            }
            done = TRUE;
        }
        else if (isdigit(*pos) || *pos == '.' || *pos == '-')
        {
            if (tok->type == NONE)
            {
                found_tok = TRUE;
                tok->type = VAL;
            }
            *name_pos++ = *pos;
        }
        else if (islower(*pos))
        {
            if (tok->type == VAL)
            {
                done = TRUE;
                pos--;
            }
            else
            {
                if (tok->type == NONE)
                {
                    found_tok = TRUE;
                    tok->type = VAR;
                }
                *name_pos++ = *pos;
            }
        }
        pos++;
    }
    *ppos = pos;
    prev_tok = *tok;

    if (found_tok && tok->type == VAL)
    {
        tok->val.fval = atof(tok->name);
    }

    return found_tok;
}

void print_tok(tok_t *tok)
{
#if DEBUG
    switch (tok->type)
    {
    case NONE:
    {
        printf("none\n");
        break;
    }
    case VAR:
    {
        printf("var: %.g, name: %s\n", tok->val.fval, tok->name);
        break;
    }
    case VAL:
    {
        printf("val: %.g, name: %s\n", tok->val.fval, tok->name);
        break;
    }
    case OP:
    {
        const char *assoc = "none"; 
        if (op_tbl[tok->val.ival].assoc == LEFT_ASSOC)
        {
            assoc = "left";
        }
        else if (op_tbl[tok->val.ival].assoc == RIGHT_ASSOC)
        {
            assoc = "right";
        }
        printf("op: %c, prec: %d, assoc: %s\n", tok->val.ival, op_tbl[tok->val.ival].prec, assoc);
        break;
    }
    default:
    {
        printf("unknown\n");
        break;
    }
    }
#endif
}

void print_toks(tok_t toks[])
{
#if DEBUG
    int i = 0;

    printf("toks\n");
    while (toks[i].type != NONE)
    {
        print_tok(&toks[i]);
        i++;
    }
#endif
}

void print_stack(stack_t *stack)
{
#if DEBUG
    int i = stack->pos - 1;

    printf(i < 0 ? "empty stack\n" : "stack\n");
    for (; i >= 0; i--)
    {
        print_tok(&stack->toks[i]);
    }
#endif
}

void fatal_error(const char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(1);
}
