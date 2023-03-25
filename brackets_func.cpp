#include "brackets_func.h"

double tree_eval (tree_t* pine, tree_node_t* tree_node)
{
    //MY_ASSERT (pine != NULL, tree_node != NULL)
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
                fprintf (pine->html_logs, "<font color = red size=4>Attempt of division by zero was delayed</font>\n\n");
                return tmp_val;
            }
            return tree_eval (pine, tree_node->left) / tree_eval (pine, tree_node->right);
    }
    return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------

int write_brackets (tree_t* pine, tree_node_t* tree_node)
{
    fprintf (pine->html_logs, "(");


    if (tree_node->left != NULL)
    {
        write_brackets (pine, tree_node->left);
    }

    if      (tree_node->node_type == TYPE_NUM) fprintf (pine->html_logs, "%d", tree_node->value);
    else if (tree_node->value     == OP_ADD)   fprintf (pine->html_logs, "+");
    else if (tree_node->value     == OP_SUB)   fprintf (pine->html_logs, "-");
    else if (tree_node->value     == OP_MUL)   fprintf (pine->html_logs, "*");
    else if (tree_node->value     == OP_DIV)   fprintf (pine->html_logs, "/");

    if (tree_node->right != NULL)
    {
        write_brackets (pine, tree_node->right);
    }

    fprintf (pine->html_logs, ")");
    return 0;
}
