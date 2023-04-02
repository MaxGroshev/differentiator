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
            return (tree_new_op_node (dif_pine, OP_ADD, dif (dif_pine, tree_node->left), dif (dif_pine, tree_node->right)));

        case OP_SUB:
            return (tree_new_op_node (dif_pine, OP_SUB, dif (dif_pine, tree_node->left), dif (dif_pine, tree_node->right)));

        case OP_MUL:
        {
            tree_node_t* dif_left  = dif (dif_pine, tree_node->left);
            tree_node_t* dif_right = dif (dif_pine, tree_node->right);
            tree_node_t* cop_left  = copy_node (dif_pine, tree_node->left);
            tree_node_t* cop_right = copy_node (dif_pine, tree_node->right);
            return tree_new_op_node (dif_pine, OP_ADD, tree_new_op_node (dif_pine, OP_MUL, dif_left, cop_right),
                                                       tree_new_op_node (dif_pine, OP_MUL, dif_right, cop_left));
            break;
        }

        case OP_DIV:
        {
            tree_node_t* dif_left  = dif (dif_pine, tree_node->left);
            tree_node_t* dif_right = dif (dif_pine, tree_node->right);
            tree_node_t* cop_left  = copy_node (dif_pine, tree_node->left);
            tree_node_t* cop_right = copy_node (dif_pine, tree_node->right);
            tree_node_t* numer = tree_new_op_node (dif_pine, OP_SUB, tree_new_op_node (dif_pine, OP_MUL, dif_left, cop_right),
                                                                     tree_new_op_node (dif_pine, OP_MUL, dif_right, cop_left));
            tree_node_t* cop_right1 = copy_node (dif_pine, tree_node->right);
            tree_node_t* denom = tree_new_op_node (dif_pine, OP_POW, cop_right1, tree_new_num_node (dif_pine, 2));
            return tree_new_op_node (dif_pine, OP_DIV, numer, denom);
        }
//         case OP_MUL:
//
//         case OP_DIV:
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
            return tree_new_op_node (dif_pine, OP_ADD, copy_node (dif_pine, tree_node->left), copy_node (dif_pine, tree_node->right));

        case OP_SUB:
            return tree_new_op_node (dif_pine, OP_SUB, copy_node (dif_pine, tree_node->left), copy_node (dif_pine, tree_node->right));

        case OP_MUL:
            return tree_new_op_node (dif_pine, OP_MUL, copy_node (dif_pine, tree_node->left), copy_node (dif_pine, tree_node->right));

        case OP_DIV:
            return tree_new_op_node (dif_pine, OP_DIV, copy_node (dif_pine, tree_node->left), copy_node (dif_pine, tree_node->right));
    }
    return NULL;
}
