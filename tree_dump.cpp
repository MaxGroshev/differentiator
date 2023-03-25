#include "tree.h"

void graph_dump (tree_t* pine)
{
    FILE* graphviz       = fopen ("./dump_info/tree_dump.dot",  "w");
    MY_ASSERT (graphviz != NULL)
    dump_graph_t graph_dump_set  = {};
    graph_dump_set.info.size = pine->size;
    graph_dump_set.info.head = &pine->root->value;
    init_graph (graphviz, &graph_dump_set);

    tree_print (graphviz, &graph_dump_set, pine->root);

    run_graphviz (graphviz, pine->html_logs, &graph_dump_set);
    fclose       (graphviz);
}

tree_node_t* tree_print (FILE* graphviz, dump_graph_t* graph_dump_set, tree_node_t* parent)
{
    make_node (graphviz, graph_dump_set, &parent->value, *graph_dump_set->nodes, &parent->right->value, &parent->left->value, parent->value);

    if (parent->left != NULL)
    {
        make_edge  (graphviz, graph_dump_set, &parent->value, &parent->left->value, *graph_dump_set->edges);
        tree_print (graphviz, graph_dump_set, parent->left);
    }
    if (parent->right != NULL)
    {
        make_edge  (graphviz, graph_dump_set, &parent->value, &parent->right->value, *graph_dump_set->edges);
        tree_print (graphviz, graph_dump_set, parent->right);
    }
}
