#include "tree.h"

void write_html_logs (int code_of_print, tree_t* pine,  tree_node_t* node)
{
    switch (code_of_print)
    {
        case T_NODE_SUC_CREATED:
            fprintf (pine->html_logs, "<font color = #70DB53 size=5>Created node: address (%p) | value  (%d)</font>\n\n", &node->value, node->value);
            break;

        case T_L_EDGE_SUC_CREATED:
            fprintf (pine->html_logs, "<font color = #6018CF size=5>Created edge: parent address (%p) | value (%d); left  (%p) | value (%d)</font>\n\n",
                                                                                          &node->value,   node->value, &node->left->value, node->value);
            break;

        case T_R_EDGE_SUC_CREATED:
            fprintf (pine->html_logs, "<font color = #6018CF size=5>Created edge: parent address (%p) | value (%d); right  (%p) | value (%d)</font>\n\n",
                                                                                    &node->value,     node->value,  &node->right->value, node->value);
            break;

        case T_TYPE_NUM_HAS_CHILD:
            fprintf (pine->html_logs, "<font color = red size=4>Node with type of num has child(ren): address (%p) | value  (%d)</font>\n", &node->value, node->value);
            break;

        case T_NODE_SUC_DELETED:
            fprintf (pine->html_logs, "<font color = orange size=5>Node was removed: address (%p) </font>\n\n", &node->value);
            break;

        case T_TREE_WAS_CLEARED:
            fprintf (pine->html_logs, "<font color = #8DB6CD size=6>Tree was cleared and deleted </font>\n\n");
            break;

        case T_FAIL_OF_CREATING_EDGE:
            fprintf (pine->html_logs, "<font color = #red size=6>ERROR of in creating edge</font>\n");
            break;

        case T_TREE_SUC_CREATED:
            fprintf   (pine->html_logs, "<pre>\n\n<font color = #8DB6CD size=6>Tree was successfully created root (%p)</font>\n\n", pine->root);
            break;
    }
}
