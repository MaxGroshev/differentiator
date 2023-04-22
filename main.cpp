#include "differentiator.h"

int main ()
{
    log_init (TREE_LOGS_HTML_DIR);
    latex_init (TREE_LOGS_TEX_DIR, TEX_DIF_PATTERN);
    struct tree_t pine = {};
    struct tree_t dif_pine = {};
    constructor (&pine);
    constructor (&dif_pine);

    pine.root = rec_descent (TREE_REC_DESCENT_DIR);
    write_latex_log (pine.root, TEX_FUNCTION);
    graph_dump (&pine);

    dif_pine.root = dif_node (pine.root , 'x');
    write_latex_log (dif_pine.root, TEX_DIF, 'x');
    graph_dump (&dif_pine);
    dif_pine.root = simpl_node (dif_pine.root, 'x');
    write_latex_log (dif_pine.root, TEX_RES, 'x');

    graph_dump (&dif_pine);

    tree_delete (pine.root);
    log_distr   ();
    latex_distr ();
}
