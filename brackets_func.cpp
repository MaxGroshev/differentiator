#include "brackets_func.h"

double tree_eval (tree_t* pine, tree_node_t* tree_node)
{
    MY_ASSERT (pine != NULL && tree_node != NULL)

    if (tree_node->node_type == TYPE_NUM)
    {
        return tree_node->value;
    }

    switch (tree_node->value)
    {
        case OP_ADD:
            return tree_eval (pine, tree_node->left) + tree_eval (pine, tree_node->right);

        case OP_SUB:
            return tree_eval (pine, tree_node->left) - tree_eval (pine, tree_node->right);

        case OP_MUL:
            return tree_eval (pine, tree_node->left) * tree_eval (pine, tree_node->right);

        case OP_DIV:
            double tmp_val = tree_eval (pine, tree_node->right);
            if (tmp_val == 0)
            {
                write_tree_logs (T_DIVISION_BY_ZERO, pine);
                return tmp_val;
            }
            return tree_eval (pine, tree_node->left) / tree_eval (pine, tree_node->right);
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------

int write_brackets (tree_t* pine, tree_node_t* tree_node)
{
    MY_ASSERT (pine != NULL && tree_node != NULL)

    fprintf (pine->html_logs, "(");
    if      (tree_node->node_type == TYPE_NUM) fprintf (pine->html_logs, "%d", tree_node->value);
    else if (tree_node->value     == OP_ADD)   fprintf (pine->html_logs, "+");
    else if (tree_node->value     == OP_SUB)   fprintf (pine->html_logs, "-");
    else if (tree_node->value     == OP_MUL)   fprintf (pine->html_logs, "*");
    else if (tree_node->value     == OP_DIV)   fprintf (pine->html_logs, "/");

    if (tree_node->left != NULL)
    {
        write_brackets (pine, tree_node->left);
    }
    if (tree_node->right != NULL)
    {
        write_brackets (pine, tree_node->right);
    }

    fprintf (pine->html_logs, ")");
    return 0;
}

tree_node_t* read_brackets (FILE* br_read, tree_t* pine, tree_node_t* tmp_node)
{
    char br_elem = 32;
    while (br_elem == 32) br_elem = fgetc (br_read);

    if (br_elem == '(')
    {
        int value = 0;
        int ret_val = fscanf (br_read, " %d", &value);
        if (ret_val != 0)
        {
            tree_node_t* tmp_node = tree_create (pine, TYPE_NUM, value);
            br_elem = fgetc (br_read);
            if (br_elem == ')') return tmp_node;
        }
        tree_node_t* tmp_node = read_brackets (br_read, pine);

        br_elem = 32;
        while (br_elem == 32) br_elem = fgetc (br_read);
        if    (br_elem == ')')  br_elem = fgetc (br_read);

        if (br_elem == '+')
        {
            tree_node_t* tmp_parent  = tree_create (pine, TYPE_OP, OP_ADD, tmp_node);
            tree_node_t* tmp_node    = read_brackets (br_read, pine);
            tree_link_r (pine, tmp_parent, tmp_node);
            return tmp_parent;
        }
        else if (br_elem == '-')
        {
            tree_node_t* tmp_parent  = tree_create (pine, TYPE_OP, OP_SUB, tmp_node);
            tree_node_t* tmp_node    = read_brackets (br_read, pine);
            tree_link_r (pine, tmp_parent, tmp_node);
            return tmp_parent;
        }
        else if (br_elem == '*')
        {
            tree_node_t* tmp_parent  = tree_create (pine, TYPE_OP, OP_MUL, tmp_node);
            tree_node_t* tmp_node    = read_brackets (br_read, pine);
            tree_link_r (pine, tmp_parent, tmp_node);
            return tmp_parent;
        }
        else if (br_elem == '/')
        {
            tree_node_t* tmp_parent  = tree_create (pine, TYPE_OP, OP_DIV, tmp_node);
            tree_node_t* tmp_node    = read_brackets (br_read, pine);
            tree_link_r (pine, tmp_parent, tmp_node);
            return tmp_parent;
        }
        else
        {
            write_brackets_logs (BR_ERROR_OF_INPUT_BRACKETS_SEQ, pine, ftell (br_read));
        }
    }
    else
    {
        write_brackets_logs (BR_NO_BRACKET_AT_THE_BEGINNING, pine, ftell (br_read));
    }
}
