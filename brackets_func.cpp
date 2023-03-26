#include "brackets_func.h"

double tree_eval (tree_t* pine, tree_node_t* tree_node)
{
    MY_ASSERT (pine != NULL && tree_node != NULL)
    printf ("Yes");
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
                fprintf (pine->html_logs, "<font color = red size=5>Attempt of division by zero was delayed</font>\n\n");
                return tmp_val;
            }
            return tree_eval (pine, tree_node->left) / tree_eval (pine, tree_node->right);
    }
    //return 0;
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

tree_node_t* read_brackets (FILE* read_br, tree_t* pine, tree_node_t* tmp_node)
{
    char c = '0';
    fscanf (read_br, " %c", &c);

    if (c == '+')
    {
        tree_node_t* tmp_node  = tree_create (pine, TYPE_OP, OP_ADD);
        tree_node_t* tmp_left  = read_brackets (read_br, pine);
        tree_node_t* tmp_right = read_brackets (read_br, pine);
        tree_link_l (pine, tmp_node, tmp_left);
        tree_link_r (pine, tmp_node, tmp_right);

        return tmp_node;
    }
    else if (c == '-')
    {
        tree_node_t* tmp_node  = tree_create (pine, TYPE_OP, OP_SUB);
        tree_node_t* tmp_left  = read_brackets (read_br, pine);
        tree_node_t* tmp_right = read_brackets (read_br, pine);
        tree_link_l (pine, tmp_node, tmp_left);
        tree_link_r (pine, tmp_node, tmp_right);

        return tmp_node;
    }
    else if (c == '*')
    {
        tree_node_t* tmp_node  = tree_create (pine, TYPE_OP, OP_MUL);
        tree_node_t* tmp_left  = read_brackets (read_br, pine);
        tree_node_t* tmp_right = read_brackets (read_br, pine);
        tree_link_l (pine, tmp_node, tmp_left);
        tree_link_r (pine, tmp_node, tmp_right);

        return tmp_node;
    }
    else if (c == '/')
    {
        tree_node_t* tmp_node  = tree_create (pine, TYPE_OP, OP_DIV);
        tree_node_t* tmp_left  = read_brackets (read_br, pine);
        tree_node_t* tmp_right = read_brackets (read_br, pine);
        tree_link_l (pine, tmp_node, tmp_left);
        tree_link_r (pine, tmp_node, tmp_right);

        return tmp_node;
    }
    else if (c == '(')
    {
        tree_node_t* tmp_node = read_brackets (read_br, pine, tmp_node);
    }
    else if (c == ')')
    {
        tree_node_t* tmp_node = read_brackets (read_br, pine);
        return tmp_node;
    }
    else
    {
        int pos = ftell (read_br);
        fseek (read_br, pos - 1, SEEK_SET);

        int value = 0;
        fscanf (read_br, "%d", &value);

        tree_node_t* tmp_node = tree_create (pine, TYPE_NUM, value);
        return tmp_node;
    }
}
