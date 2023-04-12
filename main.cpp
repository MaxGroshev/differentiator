#include "differentiator.h"

int main ()
{
    log_init   (TREE_LOGS_HTML_DIR);
    latex_init (TREE_LOGS_TEX_DIR, TEX_DIF_PATTERN);
    struct tree_t pine = {};
    struct tree_t dif_pine = {};
    constructor  (&pine);
    constructor  (&dif_pine);

    //pine.root = Mul (New_num (5), New_var (TYPE_VAR, 'x'));
    pine.root = Add (New_num (TYPE_VAR), Cos (Mul (New_num (-1), New_var (TYPE_VAR, 'x'))));
    //pine.root = Add (New_var (TYPE_VAR, 'y'), Pow (New_var (TYPE_VAR, 'x'), New_num (-1)));
    write_latex_log (pine.root, TEX_FUNCTION);
    graph_dump (&pine);

    dif_pine.root = dif_node (pine.root , 'x');
    write_latex_log (dif_pine.root, TEX_DIF, 'x');
    graph_dump (&dif_pine);
    dif_pine.root = simpl_node (&dif_pine, dif_pine.root, 'x');
    FILE* br_write = fopen ("./test_files/write_br_seq.txt", "w");
    write_brackets  (br_write, dif_pine.root);
    fclose          (br_write);
    write_latex_log (dif_pine.root, TEX_RES, 'x');

    graph_dump (&dif_pine);

    tree_delete (pine.root);
    tree_delete (dif_pine.root);
    log_distr   ();
    latex_distr ();
}
