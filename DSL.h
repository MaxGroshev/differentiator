#pragma once
#include "differentiator.h"

tree_node_t* tree_add (tree_t* pine, tree_node_t* left_node, tree_node_t* right_node);
tree_node_t* tree_sub (tree_t* pine, tree_node_t* left_node, tree_node_t* right_node);
tree_node_t* tree_mul (tree_t* pine, tree_node_t* left_node, tree_node_t* right_node);
tree_node_t* tree_div (tree_t* pine, tree_node_t* left_node, tree_node_t* right_node);
tree_node_t* tree_pow (tree_t* pine, tree_node_t* left_node, tree_node_t* right_node);

