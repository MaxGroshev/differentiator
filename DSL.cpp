#include "DSL.h"

tree_node_t* tree_add (tree_t* pine, tree_node_t* left_node, tree_node_t* right_node)
{
    return tree_new_op_node (pine, OP_ADD, left_node, right_node);
}

tree_node_t* tree_sub (tree_t* pine, tree_node_t* left_node, tree_node_t* right_node)
{
    return tree_new_op_node (pine, OP_SUB, left_node, right_node);
}

tree_node_t* tree_mul (tree_t* pine , tree_node_t* left_node, tree_node_t* right_node)
{
    return tree_new_op_node (pine, OP_MUL, left_node, right_node);
}

tree_node_t* tree_div (tree_t* pine , tree_node_t* left_node, tree_node_t* right_node)
{
    return tree_new_op_node (pine, OP_DIV, left_node, right_node);
}

tree_node_t* tree_pow (tree_t* pine , tree_node_t* left_node, tree_node_t* right_node)
{
    return tree_new_op_node (pine, OP_POW, left_node, right_node);
}
