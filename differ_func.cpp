#include "differentiator.h"

tree_node_t* dif (tree_t* dif_pine, const tree_node_t* tree_node)
{
    switch (tree_node->node_type)
    {
        case TYPE_NUM:
            return tree_new_num_node (dif_pine, 0);

        case TYPE_VAR:
            return tree_new_num_node (dif_pine, 1);

        case OP_ADD:
            return tree_add (dif_pine, dif (dif_pine, tree_node->left), dif (dif_pine, tree_node->right));

        case OP_SUB:
            return tree_sub (dif_pine, dif (dif_pine, tree_node->left), dif (dif_pine, tree_node->right));

        case OP_MUL:
        {
            return tree_add (dif_pine, tree_mul (dif_pine, dif (dif_pine, tree_node->left),  copy_node (dif_pine, tree_node->right)),
                                       tree_mul (dif_pine, dif (dif_pine, tree_node->right), copy_node (dif_pine, tree_node->left)));
        }

        case OP_DIV:
        {
            tree_node_t* numer = tree_sub (dif_pine, tree_mul (dif_pine, dif (dif_pine, tree_node->left),  copy_node (dif_pine, tree_node->right)),
                                                     tree_mul (dif_pine, dif (dif_pine, tree_node->right), copy_node (dif_pine, tree_node->left)));
            tree_node_t* denom = tree_pow (dif_pine, copy_node (dif_pine, tree_node->right), tree_new_num_node (dif_pine, 2));
            return tree_div (dif_pine, numer, denom);
        }
    }
    return NULL;
}

tree_node_t* copy_node (tree_t* dif_pine, const tree_node_t* tree_node)
{
    MY_ASSERT (tree_node != NULL && dif_pine != NULL)
    switch (tree_node->node_type)
    {
        case TYPE_NUM:
            return tree_new_num_node (dif_pine, tree_node->value);

        case TYPE_VAR:
            return tree_new_var_node (dif_pine, tree_node->node_type);

        case OP_ADD:
            return tree_add (dif_pine, copy_node (dif_pine, tree_node->left), copy_node (dif_pine, tree_node->right));

        case OP_SUB:
            return tree_sub (dif_pine, copy_node (dif_pine, tree_node->left), copy_node (dif_pine, tree_node->right));

        case OP_MUL:
            return tree_mul (dif_pine, copy_node (dif_pine, tree_node->left), copy_node (dif_pine, tree_node->right));

        case OP_DIV:
            return tree_div (dif_pine, copy_node (dif_pine, tree_node->left), copy_node (dif_pine, tree_node->right));
    }
    return NULL;
}
