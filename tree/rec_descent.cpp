#include "tree.h"

static char str[40] = "11*22/(111-109)$";
static int pos = 0;

int get_g ()
{
    int val = get_e ();
    MY_ASSERT (str[pos++] == '$');
    return val;
}

int get_e ()
{
    int val = get_t ();

    while (str[pos] == '+' || str[pos] == '-')
    {
        int op = str[pos];
        pos++;
        int val2 = get_t ();
        if   (op == '+') val += val2;
        else val -= val2;
    }
    return val;
}

int get_t ()
{
    int val = get_p ();
    while (str[pos] == '*' || str[pos] == '/')
    {
        int op = str[pos];
        pos++;
        int val2 = get_p ();
        if   (op == '*') val *= val2;
        else val /= val2;
    }
    return val;
}

int get_p ()
{
    if (str[pos] == '(')
    {
        pos++;
        int val = get_e ();
        MY_ASSERT (str[pos] == ')');
        pos++;
        return val;
    }
    else return get_n ();
}

int get_n ()
{
    int val = 0;
    int start_pos = pos;
    while (str[pos] >= '0' && str[pos] <= '9')
    {
        val = val * 10 + str[pos] - '0';
        pos++;
    }
    MY_ASSERT (start_pos < pos)
    return val;
}
