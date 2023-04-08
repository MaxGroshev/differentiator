#pragma once
#include "./LaTeX/latex.h"
#include "./tree/tree.h"
#include "logs/log_file.h"
#include "brackets_func.h"
#include "DSL.h"

//---------------------------------------------------------------------------------------------------------

tree_node_t* dif_node   (const tree_node_t* tree_node = NULL);
tree_node_t* copy_node  (const tree_node_t* tree_node = NULL);
tree_node_t* simpl_node (tree_node_t* tree_node = NULL);
