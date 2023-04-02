#pragma once
#include "differentiator.h"

tree_node_t* tree_add_node (tree_t* pine, tree_node_t* left_node, tree_node_t* right_node);
tree_node_t* tree_sub_node (tree_t* pine, tree_node_t* left_node, tree_node_t* right_node);
tree_node_t* tree_mul_node (tree_t* pine, tree_node_t* left_node, tree_node_t* right_node);
tree_node_t* tree_div_node (tree_t* pine, tree_node_t* left_node, tree_node_t* right_node);
tree_node_t* tree_pow_node (tree_t* pine, tree_node_t* left_node, tree_node_t* right_node);
tree_node_t* tree_ln_node  (tree_t* pine, tree_node_t* right_node);
tree_node_t* tree_cos_node (tree_t* pine, tree_node_t* right_node);
tree_node_t* tree_sin_node (tree_t* pine, tree_node_t* right_node);

