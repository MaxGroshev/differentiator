#include "tree.h"

static int pos_in_file = 0;
tree_node_t* rec_descent (const char* file_dir)
{
    char* buffer = read_file (file_dir);
    tree_node_t* ret_node = get_g (buffer);
    free (buffer);
    return ret_node;
}

//------------------------------------REC_DESCENT_REALIZATION--------------------------------------------------------------

tree_node_t* get_g (const char* buffer)
{
    tree_node_t* tree_node = get_e (buffer);
    if (buffer[pos_in_file++] != '$') syntax_error (T_UNREC_SYNTAX_ERROR, buffer, CUR_POS_IN_PROG);
    return tree_node;
}

tree_node_t* get_e (const char* buffer)
{
    tree_node_t* l_node = get_t (buffer);

    while (buffer[pos_in_file] == '+' || buffer[pos_in_file] == '-')
    {
        int op = buffer[pos_in_file];
        pos_in_file++;
        tree_node_t* r_node = get_t (buffer);
        if   (op == '+') l_node = tree_new_op_node (OP_ADD, l_node, r_node);
        else             l_node = tree_new_op_node (OP_SUB, l_node, r_node);
    }
    return l_node;
}

tree_node_t* get_t (const char* buffer)
{
    tree_node_t* l_node = get_p (buffer);
    while (buffer[pos_in_file] == '*' || buffer[pos_in_file] == '/')
    {
        int op = buffer[pos_in_file];
        pos_in_file++;
        tree_node_t* r_node = get_p (buffer);
        if      (op == '*')  l_node = tree_new_op_node (OP_MUL, l_node, r_node);
        else if (op == '/') l_node = tree_new_op_node (OP_DIV, l_node, r_node);
        else    syntax_error (T_NO_MUL_OR_DIV_OP, buffer, CUR_POS_IN_PROG);
    }
    return l_node;
}

tree_node_t* get_p (const char* buffer)
{
    if (buffer[pos_in_file] == '(')
    {
        pos_in_file++;
        tree_node_t* tree_node = get_e (buffer);
        if (buffer[pos_in_file] != ')') syntax_error (T_NO_CLOSED_BRACKETS, buffer, CUR_POS_IN_PROG);
        pos_in_file++;
        return tree_node;
    }
    else return get_n (buffer);
}

tree_node_t* get_n (const char* buffer)
{
    int val = 0;
    int start_pos = pos_in_file;
    while (buffer[pos_in_file] >= '0' && buffer[pos_in_file] <= '9')
    {
        val = val * 10 + buffer[pos_in_file] - '0';
        pos_in_file++;
    }
    if (start_pos >= pos_in_file) syntax_error (T_NO_NUMBER, buffer, CUR_POS_IN_PROG);
    return tree_new_num_node (val);
}

//----------------------------------------------------------------------------------------------------------------------

char* read_file (const char* file_dir)
{
    FILE* seq_file = fopen (file_dir, "r");
    MY_ASSERT (seq_file != NULL);

    struct stat file_data = {};
    stat (file_dir, &file_data);
    char* buffer = (char*) calloc (file_data.st_size, sizeof (char));
    MY_ASSERT (buffer != NULL);

    fread  (buffer, sizeof (char), file_data.st_size, seq_file);
    fclose (seq_file);
    return buffer;
}

void syntax_error (int num_of_error, const char* buffer, const char* file_name, const char* func_name, int num_of_line)
{
    fprintf (stderr, "\033[91mSyntaxERROR  \033[0m: FILE: %s, FUNCTION: %s, LINE: %d\n", file_name, func_name, num_of_line);
    switch (num_of_error)
    {
        case T_NO_CLOSED_BRACKETS:
            fprintf (stderr, "\033[91mNo closing bracket \033[0m: ");
            break;

        case T_NO_NUMBER:
            fprintf (stderr, "\033[91mWas expected num_value  \033[0m: ");
            break;

        case T_NO_MUL_OR_DIV_OP:
            fprintf (stderr, "\033[91mWas expected div or mul operation \033[0m: ");
            break;

        case T_UNREC_SYNTAX_ERROR:
            fprintf (stderr, "\033[91mName of syntax error wasn't detected. Check input. \033[0m: ");
            break;
    }
    for (int i = 0; i < pos_in_file + 1; i++)
    {
        fprintf (stderr, "%c", buffer[i]);
    }
    fprintf (stderr, "\n");
    exit (-1);
}
