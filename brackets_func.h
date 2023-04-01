#pragma once
#include "differentiator.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

enum BR_CODE_OF_PRINT
{
    BR_NO_BRACKET_AT_THE_BEGINNING = -1,
    BR_ERROR_OF_INPUT_BRACKETS_SEQ = -2,
};

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

double       tree_eval      (tree_t* pine, tree_node_t* tree_node);
int          write_brackets (FILE* br_write, tree_node_t* tree_node);
tree_node_t* read_brackets  (FILE* br_read, tree_t* pine, tree_node_t* tmp_node = NULL);

void         write_brackets_logs (int code_of_print, tree_t* pine, int position_in_file);

