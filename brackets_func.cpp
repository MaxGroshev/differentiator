#include "brackets_func.h"

double tree_eval (tree_t* pine, tree_node_t* tree_node)
{
    MY_ASSERT (pine != NULL && tree_node != NULL)

    if (tree_node->node_type == TYPE_NUM)
    {
        return tree_node->value;
    }

    switch (tree_node->node_type)
    {
        case OP_ADD:
            return tree_eval (pine, tree_node->left) + tree_eval (pine, tree_node->right);

        case OP_SUB:
            return tree_eval (pine, tree_node->left) - tree_eval (pine, tree_node->right);

        case OP_MUL:
            return tree_eval (pine, tree_node->left) * tree_eval (pine, tree_node->right);

        case OP_DIV:
        {
            double tmp_val = tree_eval (pine, tree_node->right);
            if (tmp_val == 0)
            {
                write_tree_logs (T_DIVISION_BY_ZERO, pine);
                return tmp_val;
            }
            return tree_eval (pine, tree_node->left) / tree_eval (pine, tree_node->right);
        }

        case OP_POW:
        {
            fprintf (stderr, "was made int power\n");
            int bas = tree_eval (pine, tree_node->left);
            int deg = tree_eval (pine, tree_node->right);
            if ((bas == 1) || (deg == 0)) return 1;
            else if (deg > 0)
            {
                for (int i = 1; i < deg; i++)
                {
                    bas = bas * bas;
                }
            }
            else if (deg < 0)
            {
                for (int i = 0; i < deg; i--)
                {
                    bas = bas / bas;
                }
            }
            return bas;
        }

    }
    return -1;
}

//------------------------------------------------------------------------------------------------------------------------------------------

int write_brackets (FILE* br_write, tree_node_t* tree_node)
{
    MY_ASSERT (tree_node != NULL)

    fprintf (br_write, "(");

    if (tree_node->left != NULL)
    {
        write_brackets (br_write, tree_node->left);
    }

    if      (tree_node->node_type == TYPE_NUM) fprintf (br_write, "%d", tree_node->value);
    else if (tree_node->node_type == TYPE_VAR) fprintf (br_write, "x");
    else if (tree_node->node_type == OP_ADD)   fprintf (br_write, "+");
    else if (tree_node->node_type == OP_SUB)   fprintf (br_write, "-");
    else if (tree_node->node_type == OP_MUL)   fprintf (br_write, "*");
    else if (tree_node->node_type == OP_DIV)   fprintf (br_write, "/");
    else if (tree_node->node_type == OP_POW)   fprintf (br_write, "^");

    if (tree_node->right != NULL)
    {
        write_brackets (br_write, tree_node->right);
    }

    fprintf (br_write, ")");
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
            tree_node_t* tmp_node = tree_new_num_node (pine, value);
            br_elem = fgetc (br_read);
            if (br_elem == ')') return tmp_node;
        }
        tree_node_t* tmp_node = read_brackets (br_read, pine);

        br_elem = 32;
        while (br_elem == 32) br_elem = fgetc (br_read);
        if    (br_elem == ')')  br_elem = fgetc (br_read);

        if (br_elem == '+')
        {
            tree_node_t* tmp_parent  = tree_new_op_node (pine, OP_ADD, tmp_node);
            tree_node_t* tmp_node    = read_brackets (br_read, pine);
            tree_link_r (pine, tmp_parent, tmp_node);
            return tmp_parent;
        }
        else if (br_elem == '-')
        {
            tree_node_t* tmp_parent  = tree_new_op_node (pine, OP_SUB, tmp_node);
            tree_node_t* tmp_node    = read_brackets (br_read, pine);
            tree_link_r (pine, tmp_parent, tmp_node);
            return tmp_parent;
        }
        else if (br_elem == '*')
        {
            tree_node_t* tmp_parent  = tree_new_op_node (pine, OP_MUL, tmp_node);
            tree_node_t* tmp_node    = read_brackets (br_read, pine);
            tree_link_r (pine, tmp_parent, tmp_node);
            return tmp_parent;
        }
        else if (br_elem == '/')
        {
            tree_node_t* tmp_parent  = tree_new_op_node (pine, OP_DIV, tmp_node);
            tree_node_t* tmp_node    = read_brackets (br_read, pine);
            tree_link_r (pine, tmp_parent, tmp_node);
            return tmp_parent;
        }
        else if (br_elem == '^')
        {
            tree_node_t* tmp_parent  = tree_new_op_node (pine, OP_POW, tmp_node);
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
    return NULL;
}
