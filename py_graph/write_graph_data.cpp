#include "write_graph_data.h"

int py_build_graph (const tree_node_t* tree_node, const char* pic_dir, int pattern)
{
    MY_ASSERT (tree_node != NULL)

    py_graph_init (pattern);
    py_write_equ  (tree_node);
    py_run_graph  (pic_dir);

    return 0;
}

int py_graph_init (int pattern)
{
    PYTHON_FILE = fopen ("./py_graph/graph.py", "w");
    MY_ASSERT (PYTHON_FILE != NULL);

    switch (pattern)
    {
        case PY_ONE_VAR_GRAPH:
        py_read_pattern ("./py_graph/py_patterns/one_var_graph.py");
        fprintf (PYTHON_FILE, "y = ");
        break;
    }
    return 0;
}

int py_write_equ (const tree_node_t* tree_node)
{

    fprintf (PYTHON_FILE, "(");
    if (tree_node->left != NULL)
    {
        py_write_equ (tree_node->left);
    }

    if      (tree_node->node_type == TYPE_NUM) fprintf (PYTHON_FILE, "%d", tree_node->value);
    else if (tree_node->node_type == CONST_EXP)fprintf (PYTHON_FILE, "2.7182");
    else if (tree_node->node_type == TYPE_VAR) fprintf (PYTHON_FILE, "%c", tree_node->value);
    else if (tree_node->node_type == OP_ADD)   fprintf (PYTHON_FILE, "+");
    else if (tree_node->node_type == OP_SUB)   fprintf (PYTHON_FILE, "-");
    else if (tree_node->node_type == OP_MUL)   fprintf (PYTHON_FILE, "*");
    else if (tree_node->node_type == OP_DIV)   fprintf (PYTHON_FILE, "/");
    else if (tree_node->node_type == OP_POW)   fprintf (PYTHON_FILE, "**");
    else if (tree_node->node_type == OP_LN)    fprintf (PYTHON_FILE, "np.log");
    else if (tree_node->node_type == OP_LOG)   fprintf (PYTHON_FILE, "np.log");
    else if (tree_node->node_type == OP_SIN)   fprintf (PYTHON_FILE, "np.sin");
    else if (tree_node->node_type == OP_COS)   fprintf (PYTHON_FILE, "np.cos");
    else if (tree_node->node_type == OP_TG)    fprintf (PYTHON_FILE, "np.tg");
    else if (tree_node->node_type == OP_CTG)   fprintf (PYTHON_FILE, "np.ctg");

    if (tree_node->right != NULL)
    {
        py_write_equ (tree_node->right);
    }

    fprintf (PYTHON_FILE, ")");
    return 0;
}

int py_read_pattern (const char* pat_dir)
{
    FILE* pat_file = fopen (pat_dir, "r");
    MY_ASSERT (pat_file != NULL);

    struct stat pat_file_data = {};
    stat (pat_dir, &pat_file_data);
    char* buffer = (char*) calloc (pat_file_data.st_size, sizeof (char));
    MY_ASSERT (buffer != NULL);

    fread  (buffer, sizeof (char), pat_file_data.st_size, pat_file);
    fwrite (buffer, sizeof (char), pat_file_data.st_size, PYTHON_FILE);
    free   (buffer);
    fclose (pat_file);


    return 0;
}

int py_run_graph (const char* pic_dir)
{
    fprintf (PYTHON_FILE, "\nax.plot (x, y)\n"
                          "plt.savefig('%s')\n", pic_dir);
    fclose  (PYTHON_FILE);
    call_system ("python3.11 ./py_graph/graph.py"); //improve (not everyone has this ver of python)

    return 0;
}

void py_call_system (const char* command)
{
    printf ("hh");
    int dupper = 0;
    dupper = (2);
    close (2);
    system (command);
    dup2 (dupper, 2);
    close (dupper);
}
