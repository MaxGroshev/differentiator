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
    //dif_pine.root = dif_node (pine.root, 'x');
    //int res  = tree_eval (pine.root);
    printf ("res =\n");
    //graph_dump  (&dif_pine);
    //write_latex_log (dif_pine.root, TEX_RES, 'x');

    tree_delete (pine.root);
    log_distr   ();
    latex_distr ();
}
