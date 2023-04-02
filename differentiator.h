#pragma once
#include "./tree/tree.h"
#include "logs/log_file.h"
#include "brackets_func.h"
#include "DSL.h"

//---------------------------------------------------------------------------------------------------------

tree_node_t* dif_node      (tree_t* pine, const tree_node_t* tree_node = NULL);
tree_node_t* copy_node (tree_t* dif_pine, const tree_node_t* tree_node = NULL);
