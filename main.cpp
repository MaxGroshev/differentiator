#include "differentiator.h"

int main ()
{
    log_init   (TREE_LOGS_HTML_DIR);
    latex_init (TREE_LOGS_TEX_DIR, TEX_DIF_PATTERN);
    struct tree_t pine = {};
    struct tree_t dif_pine = {};
    constructor  (&pine);
    constructor  (&dif_pine);

    pine.root = Pow (New_var (TYPE_VAR), New_var (TYPE_VAR));
    pine.root = Pow (pine.root, Add (New_var (TYPE_VAR), Cos (New_var (TYPE_VAR))));
    write_latex_log (pine.root, TEX_FUNCTION);
    graph_dump (&pine);

    dif_pine.root = dif_node (pine.root);
    write_latex_log (dif_pine.root, TEX_DIF);
    graph_dump (&dif_pine);

    FILE* br_write = fopen ("./test_files/write_br_seq.txt", "w");
    write_brackets (br_write, dif_pine.root);
    fclose         (br_write);

    dif_pine.root = simpl_node (&pine, dif_pine.root);
    write_latex_log (dif_pine.root, TEX_SIMPLIFIED);
    graph_dump (&dif_pine);

    tree_delete (pine.root);
    tree_delete (dif_pine.root);
    log_distr   ();
    latex_distr ();
}
