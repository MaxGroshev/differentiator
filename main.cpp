#include "differentiator.h"

int main ()
{
    log_init (TREE_LOGS_HTML_DIR);
    struct tree_t pine = {};
    constructor (&pine);

    pine.root = rec_descent (TREE_REC_DESCENT_DIR);
    int res  = tree_eval (pine.root);
    printf ("res = %d\n", res);
    graph_dump  (&pine);

    tree_delete (pine.root);
    log_distr   ();
}
