#include "../differentiator.h"
#include "log_file.h"

static FILE* LOG_FILE = NULL;

int log_init (const char* log_file_name)
{
    LOG_FILE = fopen (log_file_name, "w");
    MY_ASSERT (LOG_FILE != NULL);
    fprintf   (LOG_FILE, "<pre>\n\n");
    return 0;
}

void write_tree_logs (int code_of_print, tree_t* pine,  tree_node_t* node)
{
    MY_ASSERT (pine != NULL && LOG_FILE != NULL);
    switch (code_of_print)
    {
        case T_NODE_SUC_CREATED:
            fprintf (LOG_FILE, "<font color = #70DB53 size=5>Created node: address (%p) | value  (%d)</font>\n\n", &node->value, node->node_type);
            break;

        case T_L_EDGE_SUC_CREATED:
            fprintf (LOG_FILE, "<font color = #6018CF size=5>Created edge: parent address (%p) | value (%d); left  (%p) | value (%d)</font>\n\n",
                                                                                          &node->value,   node->value, &node->left->value, node->value);
            break;

        case T_R_EDGE_SUC_CREATED:
            fprintf (LOG_FILE, "<font color = #6018CF size=5>Created edge: parent address (%p) | value (%d); right  (%p) | value (%d)</font>\n\n",
                                                                                    &node->value,     node->value,  &node->right->value, node->value);
            break;

        case T_TYPE_NUM_HAS_CHILD:
            fprintf (LOG_FILE, "<font color = red size=4>Node with type of num has child(ren): address (%p) | value  (%d)</font>\n", &node->value, node->value);
            break;

        case T_NODE_SUC_DELETED:
            fprintf (LOG_FILE, "<font color = orange size=5>Node was removed: address (%p) </font>\n\n", &node->value);
            break;

        case T_TREE_WAS_CLEARED:
            fprintf (LOG_FILE, "<font color = #8DB6CD size=6>Tree was cleared and deleted </font>\n\n");
            break;

        case T_FAIL_OF_CREATING_EDGE:
            fprintf (LOG_FILE, "<font color = #red size=6>ERROR of in creating edge</font>\n");
            break;

        case T_TREE_SUC_CREATED:
            fprintf   (LOG_FILE, "\n\n<font color = #8DB6CD size=6>Tree was successfully created root (%p)</font>\n\n", &pine->root->value);
            break;
    }
}

void write_brackets_logs (int code_of_print, tree_t* pine, int position_in_file)
{
    MY_ASSERT (LOG_FILE != NULL);
    switch (code_of_print)
    {
        case BR_NO_BRACKET_AT_THE_BEGINNING:
            fprintf (LOG_FILE, "<pre>\n\n<font color = red size=5>No bracket at the beginning: position in file (%d)</font>\n\n", position_in_file);
            fprintf (stderr, "Running of program was terminated-check logs\n");
            exit (-1);

        case BR_ERROR_OF_INPUT_BRACKETS_SEQ:
            fprintf (LOG_FILE, "<pre>\n\n<font color = red size=5>Error of input of seq: position in file (%d)</font>\n\n", position_in_file);
            fprintf (stderr, "Running of program was terminated-check logs\n");
            exit (-2);
    }
}

int pic_log (const char* label, const char* name_of_pic)
{
    fprintf (LOG_FILE, "\n\n<font color = #8DB6CD size=6>%s</font>\n\n", label);
    fprintf (LOG_FILE, "<img src = %s width=""800"" height=""350"">\n", name_of_pic);
    return 0;
}

int log_distr ()
{
    fclose (LOG_FILE);
    return 0;
}
