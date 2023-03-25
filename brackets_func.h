#pragma once
#include "tree.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

double tree_eval      (tree_t* pine, tree_node_t* tree_node);
int    write_brackets (tree_t* pine, tree_node_t* tree_node);
int    read_brackets  (tree_t* pine, tree_node_t* tree_node);
