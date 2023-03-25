#include "tree.h"

tree_node_t* constructor (tree_t* pine, tree_type value)
{
    MY_ASSERT (pine != NULL);

    pine->size = 1;
    pine->root = (tree_node_t*) calloc (pine->size, sizeof (tree_node_t));
    pine->html_logs = fopen ("./dump_info/tree_dump.html", "w");
    MY_ASSERT (pine->root != NULL && pine->html_logs != NULL);
    fprintf   (pine->html_logs, "<pre>\n\n<font color = #8DB6CD size=6>Tree was successfully created root (%p)</font>\n\n", pine->root);

    pine->root->value = value;
    pine->root->left  = NULL;
    pine->root->right = NULL;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

tree_node_t* tree_create (tree_t* pine, tree_type value, tree_node_t* l_child, tree_node_t* r_child)
{
    tree_node_t* tmp_node = (tree_node_t*) calloc (1, sizeof (tree_node_t));
    MY_ASSERT (tmp_node != NULL);

    pine->size++;
    tmp_node->value = value;

    if (pine->root == l_child || pine->root == r_child) pine->root = tmp_node;
    if (l_child != NULL)
    {
        tree_link_l (pine, tmp_node, l_child);
    }
    if (r_child != NULL)
    {
        tree_link_r (pine, tmp_node, r_child);
    }

    // tmp_node->left  = NULL;
    // tmp_node->right = NULL;

    fprintf (pine->html_logs, "<font color = #70DB53 size=4>Created node: address (%p) | value  (%d)</font>\n\n", tmp_node, tmp_node->value);
    return  tmp_node;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

tree_node_t* tree_link_l (tree_t* pine, tree_node_t* parent, tree_node_t* child)
{
    MY_ASSERT (parent != NULL && child != NULL);

    if (parent->left == NULL)
    {
        parent->left  = child;
        fprintf (pine->html_logs, "<font color = #6018CF size=4>Created edge: parent address (%p) | value (%d); left  (%p) | value (%d)</font>\n\n",
                                                                              parent,            parent->value, child, child->value);
        return parent->left;
    }
    fprintf (stderr, "Impossible to add node to not terminal\n");
    return NULL;
}

tree_node_t* tree_link_r (tree_t* pine, tree_node_t* parent, tree_node_t* child)
{
   MY_ASSERT (parent != NULL && child != NULL);

    if (parent->right == NULL)
    {
        parent->right = child;
        fprintf (pine->html_logs, "<font color = #6018CF size=4>Created edge: parent address (%p) | value (%d); right  (%p) | value (%d)</font>\n\n",
                                                                              parent,            parent->value, child, child->value);
        return parent->right;
    }
    fprintf (stderr, "Impossible to add node to not terminal\n");

    return NULL;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

tree_node_t* tree_search (tree_node_t* tree_root, tree_node_t* node)
{

    printf ("here\n");
    MY_ASSERT (tree_root != NULL)
    if (tree_root->left != NULL)
    {
        //printf ("here\n");
        if (tree_root->left == node || tree_root->right == node)
        {
            printf ("O---K\n");
            return tree_root;
        }
        //MY_ASSERT (tree_root->left != NULL)
        tree_node_t* tree_root = tree_search (tree_root->left, node);
        printf ("returned\n");

        if (tree_root->left == node || tree_root->right == node)
        {
            return tree_root;
        }
    }
    // if (tree_root->right != NULL)
    // {
    //     if (tree_root->left == node || tree_root->right == node)
    //     {
    //         printf ("O---K\n");
    //         return tree_root;
    //     }
    //     tree_node_t* tree_root = tree_search (tree_root->right, node);
    //     if (tree_root->left == node || tree_root->right == node)
    //     {
    //         return tree_root;
    //     }
    // }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

tree_node_t* tree_remove  (tree_t* pine, tree_node_t* node)
{
    MY_ASSERT (node != NULL);
    tree_node_t* ret_node = tree_search (pine->root, node);
    MY_ASSERT (ret_node != NULL);

    if (ret_node->right == node)
    {
        free (ret_node->right);
        ret_node->right = NULL;
    }
    else if (ret_node->left == node)
    {
        free (ret_node->left);
        ret_node->left = NULL;
    }
    pine->size--;
    fprintf (pine->html_logs, "<font color = oranged size=4>Node was removed: address (%p) </font>\n\n", node);
    return node;
}

tree_node_t* tree_delete (tree_t* pine, tree_node_t* tree_root)
{
    MY_ASSERT (tree_root != NULL);
    //printf ("%d\n", tree_root->value);
    if (tree_root->left != NULL)
    {
        tree_delete (pine, tree_root->left);
    }
    if (tree_root->right != NULL)
    {
        tree_delete (pine, tree_root->right);
    }
    free (tree_root);

    fprintf (pine->html_logs, "<font color = red size=4>Node was deleted: address (%p) </font>\n\n", &tree_root->value);
    if (tree_root == pine->root)
    {
        fprintf (pine->html_logs, "<font color = #8DB6CD size=6>Tree was cleared and deleted </font>\n\n");
        fclose  (pine->html_logs);
    }

    return NULL;
}
