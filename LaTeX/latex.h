#pragma once
#define DEBUG
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "../tree/tree.h"
#include "../py_graph/write_graph_data.h"
#include "TEX_DSL.h"
#include "my_ASSERT.h"

//-----------------------------------------------------------------------------------------------------------------------------------------------------------

static FILE* LATEX_FILE = NULL;

//-----------------------------------------------------------------------------------------------------------------------------------------------------------

enum TEX_PATTERNS
{
    TEX_DIF_PATTERN = 1,
};

enum TEX_EQU_TYPE
{
    TEX_FUNCTION     = 1,
    TEX_DIF          = 2,
    TEX_DIF_IN_POINT = 3,
    TEX_SIMPLIFIED   = 4,
    TEX_RES          = 5,
};

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct stat;

//-----------------------------------------------------------------------------------------------------------------------------------------------------------

int latex_init        (const char* tex_dir, int pattern);
int read_pattern      (const char* pat_dir);
int write_latex_log   (tree_node_t* tree_node, int equ_type = 0, char dif_var = 'x', const char* text = NULL);
int write_func_in_tex (const tree_node_t* tree_node, int* is_one_arg_func, char dif_var = 'x');
int latex_distr       ();
