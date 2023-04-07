#include "differentiator.h"

int main ()
{
    log_init   (TREE_LOGS_HTML_DIR);
    latex_init (TREE_LOGS_TEX_DIR, TEX_DIF_PATTERN);

    struct tree_t pine = {};
    struct tree_t dif_pine = {};
    constructor  (&pine);
    constructor  (&dif_pine);

    pine.root = tree_new_op_node (OP_POW,  tree_new_var_node (TYPE_VAR), tree_new_var_node (TYPE_VAR));
    pine.root = tree_new_op_node (OP_POW, pine.root, tree_new_op_node (OP_ADD, tree_new_var_node (TYPE_VAR), tree_new_op_node (OP_COS, NULL, tree_new_var_node (TYPE_VAR))));
    write_latex_log (pine.root, TEX_FUNCTION);

    dif_pine.root = dif_node (pine.root);
    write_latex_log (dif_pine.root, TEX_DIF);

    FILE* br_write = fopen ("./test_files/write_br_seq.txt", "w");
    write_brackets (br_write, dif_pine.root);
    fclose         (br_write);

    graph_dump (&pine);
    graph_dump (&dif_pine);


    tree_delete (pine.root);
    tree_delete (dif_pine.root);

    log_distr   ();
    latex_distr ();
}
