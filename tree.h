#pragma once
#define DEBUG
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./graph_lib/graphviz.h"
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
    tree_node_t* root;
    size_t       size;
    FILE*   html_logs;
};

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

enum NODE_TYPE
{
    TYPE_NUM = 1,
    TYPE_OP  = 2,
};

enum OPER_TYPE
{
    OP_ADD = 1,
    OP_SUB = 2,
    OP_MUL = 3,
    OP_DIV = 4,
};

enum TREE_CODE_OF_PRINT
{
    T_TREE_SUC_CREATED      =  0,
    T_NODE_SUC_CREATED      =  1,
    T_FAIL_OF_CREATING_NODE = -1,
    T_L_EDGE_SUC_CREATED    =  2,
    T_R_EDGE_SUC_CREATED    =  3,
    T_FAIL_OF_CREATING_EDGE = -2,
    T_TREE_PRINT            =  4,
    T_NODE_SUC_DELETED      =  5,
    T_TREE_WAS_CLEARED      =  6,
    T_TYPE_NUM_HAS_CHILD    = -3,
};

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

tree_node_t* constructor (tree_t* pine, int node_type, tree_data_type value);
tree_node_t* tree_create (tree_t* pine, int node_type, tree_data_type value, tree_node_t* l_child = NULL, tree_node_t* r_child = NULL);

tree_node_t* tree_link_l (tree_t* pine, tree_node_t* parent, tree_node_t* child);
tree_node_t* tree_link_r (tree_t* pine, tree_node_t* parent, tree_node_t* child);
tree_node_t* tree_remove (tree_t* pine, tree_node_t* node);
tree_node_t* tree_search (tree_node_t* tree_root, tree_node_t* node);

void         graph_dump      (tree_t* pine);
tree_node_t* tree_print      (FILE* graphviz, dump_graph_t* graph_dump_set, tree_node_t* parent);
void         write_html_logs (int code_of_print, tree_t* pine = NULL, tree_node_t* node = NULL);


tree_node_t* tree_delete (tree_t* pine, tree_node_t* tree_root);
