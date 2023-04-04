#include "differentiator.h"

int main ()
{
    log_init ("./logs/log_file.html");

    struct tree_t pine = {};
    struct tree_t dif_pine = {};
    constructor  (&pine);
    constructor  (&dif_pine);

    FILE* br_read = fopen ("./test_files/read_br_seq.txt", "r");
    MY_ASSERT (br_read != NULL);
    //read_brackets (br_read, &pine);
    fclose    (br_read);
    // double res = tree_eval (&pine, pine.root);
    // printf ("%lg", res);

    pine.root = tree_new_op_node (OP_SIN, NULL, tree_new_var_node (TYPE_VAR));
    pine.root = tree_new_op_node (OP_DIV, pine.root, tree_new_var_node (TYPE_VAR));
    //tree_new_op_node (&pine, OP_DIV, left_node, right_node);
    //tree_node_t* node  = tree_new_op_node (&pine, OP_CTG, NULL, right_node);

    dif_pine.root = dif_node (pine.root);

    FILE* br_write = fopen ("./test_files/write_br_seq.txt", "w");
    write_brackets (br_write, dif_pine.root);
    fclose         (br_write);

    graph_dump (&pine);
    graph_dump (&dif_pine);


    tree_delete (pine.root);
    tree_delete (dif_pine.root);

    log_distr ();
}
