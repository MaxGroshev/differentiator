#include "tree.h"

void graph_dump (tree_t* pine)
{
    MY_ASSERT (pine != NULL);

    FILE* graphviz       = fopen ("dump_info/tree_dump.dot",  "w");
    MY_ASSERT (graphviz != NULL)
    dump_graph_t graph_dump_set  = {};
    graph_dump_set.info.size = pine->size;
    graph_dump_set.info.head = &pine->root->value;
    graph_dump_set.info.save_pic_to = "../logs/logs_pic/";
    init_graph   (graphviz, &graph_dump_set);
    tree_print   (graphviz, &graph_dump_set, pine->root);

    run_graphviz (graphviz, &graph_dump_set);
    pic_log      ("Here is the print of your tree", "../dump_info/tree_dump.png");
    fclose       (graphviz);
}

int tree_print (FILE* graphviz, dump_graph_t* graph_dump_set, tree_node_t* parent)
{
    if (parent->node_type == TYPE_NUM)
    {
        graph_dump_set->nodes->fillcolor = "#FF8C69";
        graph_dump_set->nodes->label     = "TYPE_NUM";
        print_int_node (graphviz, graph_dump_set, &parent->value, *graph_dump_set->nodes, &parent->right->value, &parent->left->value, parent->value);
    }
    else if (parent->node_type == TYPE_VAR)
    {
        graph_dump_set->nodes->fillcolor = "#7FC7FF";
        graph_dump_set->nodes->label     = "TYPE_VAR";
        print_char_node (graphviz, graph_dump_set, &parent->value, *graph_dump_set->nodes, &parent->right->value, &parent->left->value, parent->node_type);
    }
    else
    {
        graph_dump_set->nodes->fillcolor = "#77DD77";
        graph_dump_set->nodes->label     = "TYPE_OP";

        switch (parent->node_type)
        {
            case OP_ADD:
                print_char_node (graphviz, graph_dump_set, &parent->value, *graph_dump_set->nodes, &parent->right->value, &parent->left->value, OP_ADD);
                break;
            case OP_SUB:
                print_char_node (graphviz, graph_dump_set, &parent->value, *graph_dump_set->nodes, &parent->right->value, &parent->left->value, OP_SUB);
                break;
            case OP_MUL:
                print_char_node (graphviz, graph_dump_set, &parent->value, *graph_dump_set->nodes, &parent->right->value, &parent->left->value, OP_MUL);
                break;
            case OP_DIV:
                print_char_node (graphviz, graph_dump_set, &parent->value, *graph_dump_set->nodes, &parent->right->value, &parent->left->value, OP_DIV);
                break;
            case OP_POW:
                print_char_node (graphviz, graph_dump_set, &parent->value, *graph_dump_set->nodes, &parent->right->value, &parent->left->value, OP_POW);
                break;
            case OP_SQR:
                print_str_node  (graphviz, graph_dump_set, &parent->value, *graph_dump_set->nodes, &parent->right->value, &parent->left->value, "sqr");
                break;
            case OP_LN:
                print_str_node  (graphviz, graph_dump_set, &parent->value, *graph_dump_set->nodes, &parent->right->value, &parent->left->value, "ln");
                break;
            case OP_LOG:
                print_str_node  (graphviz, graph_dump_set, &parent->value, *graph_dump_set->nodes, &parent->right->value, &parent->left->value, "log");
                break;
            case OP_SIN:
                print_str_node  (graphviz, graph_dump_set, &parent->value, *graph_dump_set->nodes, &parent->right->value, &parent->left->value, "sin");
                break;
            case OP_COS:
                print_str_node  (graphviz, graph_dump_set, &parent->value, *graph_dump_set->nodes, &parent->right->value, &parent->left->value, "cos");
                break;
            case OP_TG:
                print_str_node  (graphviz, graph_dump_set, &parent->value, *graph_dump_set->nodes, &parent->right->value, &parent->left->value, "tg");
                break;
            case OP_CTG:
                print_str_node  (graphviz, graph_dump_set, &parent->value, *graph_dump_set->nodes, &parent->right->value, &parent->left->value, "ctg");
                break;
        }
    }

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
    return 0;
}