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
//
//         case OP_SUB:
//
//         case OP_MUL:
//
//         case OP_DIV:
    }
    return NULL;
}
