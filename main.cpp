#include "tree.h"
#include "brackets_func.h"

int main ()
{
    struct tree_t pine = {};
    constructor (&pine, TYPE_NUM, 5);

    tree_node_t* node1 = tree_create (&pine, TYPE_NUM, 7);
    tree_node_t* node3 = tree_create (&pine, TYPE_OP, OP_ADD, pine.root, node1);
    tree_node_t* node4 = tree_create (&pine, TYPE_NUM, 10);
    tree_node_t* node2 = tree_create (&pine, TYPE_OP,  OP_MUL, node3, node4);

    double res = tree_eval (&pine, pine.root);
    printf ("%lg", res);

    write_brackets (&pine, pine.root);

    graph_dump  (&pine);

    tree_delete (&pine, pine.root);
}
