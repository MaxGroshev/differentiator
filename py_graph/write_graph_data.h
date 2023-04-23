#pragma once
#define DEBUG
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "../tree/tree.h"
#include "my_ASSERT.h"

//-----------------------------------------------------------------------------------------------------------------------------------------------------------

static FILE* PYTHON_FILE = NULL;

//-----------------------------------------------------------------------------------------------------------------------------------------------------------

enum PY_PATTERNS
{
    PY_ONE_VAR_GRAPH = 1,
};


enum PY_GRAPH_TYPE
{

};

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct stat;

//-----------------------------------------------------------------------------------------------------------------------------------------------------------

int py_graph_init (int pattern);

int py_build_graph (const tree_node_t* tree_node, const char* pic_dir, int pattern);
int py_write_equ (const tree_node_t* tree_node);

int py_read_pattern   (const char* pat_dir);
int py_run_graph (const char* pic_dir);
void py_call_system (const char* command);

