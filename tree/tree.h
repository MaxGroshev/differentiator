#pragma once
#define DEBUG
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "./graph_lib/graphviz.h"
#include "../logs/log_file.h"
#include "my_ASSERT.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef int tree_data_type;

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct tree_node_t
{
    int            node_type;
    tree_data_type value;
    tree_node_t*   right;
    tree_node_t*   left;
};

struct tree_t
{
    tree_node_t* root = NULL;
    size_t       size = 0;
};

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

enum NODE_TYPE
{
    TYPE_NUM = 1,
    TYPE_VAR = 120,
    OP_ADD = 43,
    OP_SUB = 45,
    OP_MUL = 42,
    OP_DIV = 47,
    OP_POW = 94,
    OP_SIN = 50,
    OP_COS = 51,
    OP_LN  = 52,
    OP_SQR = 54,
    OP_EXP = 55,
    OP_LOG = 56,
    OP_TG  = 57,
    OP_CTG = 58,
};

enum TREE_CODE_OF_PRINT
{
    T_TREE_SUC_CREATED      =  0,
    T_NODE_SUC_CREATED      =  1,
    T_L_EDGE_SUC_CREATED    =  2,
    T_R_EDGE_SUC_CREATED    =  3,
    T_TREE_PRINT            =  4,
    T_NODE_SUC_DELETED      =  5,
    T_TREE_WAS_CLEARED      =  6,

    T_FAIL_OF_CREATING_NODE = -1,
    T_FAIL_OF_CREATING_EDGE = -2,
    T_TYPE_NUM_HAS_CHILD    = -3,
    T_DIVISION_BY_ZERO      = -4,
};

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

tree_t*      constructor       (tree_t* pine);
tree_node_t* tree_new_num_node (tree_data_type value);
tree_node_t* tree_new_var_node (int node_type);
tree_node_t* tree_new_op_node  (int node_type, tree_node_t* l_child = NULL, tree_node_t* r_child = NULL);

tree_node_t* tree_link_l (tree_node_t* parent, tree_node_t* child);
tree_node_t* tree_link_r (tree_node_t* parent, tree_node_t* child);
tree_node_t* tree_remove (tree_t* pine, tree_node_t* node);
tree_node_t* tree_search (tree_node_t* tree_root, tree_node_t* node);

void         graph_dump      (tree_t* pine);
int          tree_print      (dump_graph_t* graph_dump_set, tree_node_t* parent);
void         write_tree_logs (int code_of_print, tree_node_t* node = NULL);

tree_node_t* tree_delete (tree_node_t* tree_node);

void         signal_handler (int signal);
