#include "tree.h"

static int pos_in_file = 0;

tree_node_t* rec_descent (const char* file_dir)
{

    char* buffer = read_file (file_dir);
    tree_node_t* ret_node =  get_g (buffer);
    free (buffer);
    return ret_node;
}

//------------------------------------REC_DESCENT_REALIZATION--------------------------------------------------------------

tree_node_t* get_g (const char* buffer)
{
    tree_node_t* tree_node = get_e (buffer);
    MY_ASSERT (buffer[pos_in_file++] == '$');
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
        if   (op == '*') l_node = tree_new_op_node (OP_MUL, l_node, r_node);
        else             l_node = tree_new_op_node (OP_DIV, l_node, r_node);
    }
    return l_node;
}

tree_node_t* get_p (const char* buffer)
{
    if (buffer[pos_in_file] == '(')
    {
        pos_in_file++;
        tree_node_t* tree_node = get_e (buffer);
        MY_ASSERT (buffer[pos_in_file] == ')');
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
    MY_ASSERT (start_pos < pos_in_file)
    return tree_new_num_node (val);
}

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
