#include "tree.h"

int main ()
{
    struct tree_t pine = {};
    constructor (&pine, 0);

    tree_node_t* node1 = tree_create (&pine, 1);
    tree_node_t* node3 = tree_create (&pine, 3);
    tree_node_t* node4 = tree_create (&pine, 4);
    tree_node_t* node2 = tree_create (&pine, 2, node3, node4);

    // tree_node_t* node5 = tree_create (&pine, 5);
    // tree_node_t* node6 = tree_create (&pine, 6);
    // tree_node_t* node7 = tree_create (&pine, 7);
    // tree_node_t* node8 = tree_create (&pine, 8);
    // tree_node_t* node9 = tree_create (&pine, 9);

    tree_link_l (&pine, pine.root, node1);
    tree_link_r (&pine, pine.root, node2);
    // tree_link_l (&pine, node1,     node3);
    // tree_link_r (&pine, node1,     node4);
    // tree_link_l (&pine, node2,     node5);
    // tree_link_r (&pine, node2,     node9);
    // tree_link_l (&pine, node3,     node7);
    // tree_link_r (&pine, node5,     node8);
    // tree_link_l (&pine, node5,     node6);
    //tree_node_t* ret_node = tree_search (pine.root, node3);
    // MY_ASSERT (ret_node != NULL);
   // printf ("%d \n", ret_node->value);


    //printf ("%p %d\n", node2->right, node2->right->value);
    //tree_remove  (&pine, node5);


    graph_dump  (&pine);

    tree_delete (&pine, pine.root);
}
