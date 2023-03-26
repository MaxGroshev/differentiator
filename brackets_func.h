#pragma once
#include "tree.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

double       tree_eval      (tree_t* pine, tree_node_t* tree_node);
int          write_brackets (tree_t* pine, tree_node_t* tree_node);
tree_node_t* read_brackets  (FILE* read_br, tree_t* pine, tree_node_t* tmp_node = NULL);
