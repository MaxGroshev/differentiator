#include "DSL.h"

tree_node_t* tree_add_node (tree_node_t* left_node, tree_node_t* right_node)
{
    return tree_new_op_node (OP_ADD, left_node, right_node);
}

tree_node_t* tree_sub_node (tree_node_t* left_node, tree_node_t* right_node)
{
    return tree_new_op_node (OP_SUB, left_node, right_node);
}

tree_node_t* tree_mul_node (tree_node_t* left_node, tree_node_t* right_node)
{
    return tree_new_op_node (OP_MUL, left_node, right_node);
}

tree_node_t* tree_div_node (tree_node_t* left_node, tree_node_t* right_node)
{
    return tree_new_op_node (OP_DIV, left_node, right_node);
}

tree_node_t* tree_pow_node (tree_node_t* left_node, tree_node_t* right_node)
{
    return tree_new_op_node (OP_POW, left_node, right_node);
}

tree_node_t* tree_ln_node (tree_node_t* right_node)
{
    return tree_new_op_node (OP_LN, NULL, right_node);
}

tree_node_t* tree_cos_node (tree_node_t* right_node)
{
    return tree_new_op_node (OP_COS, NULL, right_node);
}

tree_node_t* tree_sin_node (tree_node_t* right_node)
{
    return tree_new_op_node (OP_SIN, NULL, right_node);
}

tree_node_t* tree_tg_node (tree_node_t* right_node)
{
    return tree_new_op_node (OP_SIN, NULL, right_node);
}

tree_node_t* tree_ctg_node (tree_node_t* right_node)
{
    return tree_new_op_node (OP_SIN, NULL, right_node);
}

