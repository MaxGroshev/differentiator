#include "differentiator.h"


int main ()
{
    log_init      (TREE_LOGS_HTML_DIR);
    latex_init    (TREE_LOGS_TEX_DIR, TEX_DIF_PATTERN);

    struct tree_t pine = {};
    struct tree_t dif_pine = {};
    constructor (&pine);
    constructor (&dif_pine);

    pine.root = Add (New_num (TYPE_VAR), Cos (Ln (New_var (TYPE_VAR, 'x'))));
    //pine.root = rec_descent (TREE_REC_DESCENT_DIR);

    write_latex_log (pine.root, TEX_FUNCTION);
    graph_dump (pine.root);

    dif_pine.root = dif_node (pine.root , 'x');
    write_latex_log (dif_pine.root, TEX_DIF, 'x');
    graph_dump      (dif_pine.root);
    dif_pine.root = simpl_node (dif_pine.root, 'x');
    graph_dump      (dif_pine.root);
    write_latex_log (dif_pine.root, TEX_RES, 'x');

   // py_build_graph (dif_pine.root, "./py_graph/first_pic.png", PY_ONE_VAR_GRAPH);

    tree_delete (pine.root);
    tree_delete (dif_pine.root);
    log_distr   ();
    latex_distr ();
}
