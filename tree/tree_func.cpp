#include "tree.h"

tree_t* constructor (tree_t* pine)
{
    MY_ASSERT (pine!= NULL);

    pine->size = 0;
    pine->root = NULL;
    write_tree_logs (T_TREE_SUC_CREATED, pine);

    return pine;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

tree_node_t* tree_new_num_node (tree_t* pine, tree_data_type value)
{
    tree_node_t* tmp_node = (tree_node_t*) calloc (1, sizeof (tree_node_t));
    MY_ASSERT   (tmp_node != NULL);


    tmp_node->value     = value;
    tmp_node->node_type = TYPE_NUM;

    if (pine->size == 0) pine->root = tmp_node;
    pine->size++;
    write_tree_logs (T_NODE_SUC_CREATED, pine, tmp_node);
    return  tmp_node;
}

tree_node_t* tree_new_var_node (tree_t* pine, int node_type)
{
    tree_node_t* tmp_node = (tree_node_t*) calloc (1, sizeof (tree_node_t));
    MY_ASSERT   (tmp_node != NULL);

    tmp_node->node_type = TYPE_VAR;
    if (pine->size == 0) pine->root = tmp_node;
    pine->size++;

    write_tree_logs (T_NODE_SUC_CREATED, pine, tmp_node);
    return  tmp_node;
}

tree_node_t* tree_new_op_node (tree_t* pine, int node_type, tree_node_t* l_child, tree_node_t* r_child)
{
    tree_node_t* tmp_node = (tree_node_t*) calloc (1, sizeof (tree_node_t));
    MY_ASSERT   (tmp_node != NULL);
    pine->size++;

    tmp_node->node_type = node_type;
    write_tree_logs (T_NODE_SUC_CREATED, pine, tmp_node);
    if (pine->size == 0) pine->root = tmp_node;
    if (pine->root == l_child || pine->root == r_child) pine->root = tmp_node;
    if (l_child != NULL) tree_link_l (pine, tmp_node, l_child);
    if (r_child != NULL) tree_link_r (pine, tmp_node, r_child);
    MY_ASSERT   (tmp_node != NULL);

    return  tmp_node;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

tree_node_t* tree_link_l (tree_t* pine, tree_node_t* parent, tree_node_t* child)
{
    MY_ASSERT (parent != NULL && child != NULL);

    if (parent->node_type == TYPE_NUM) write_tree_logs (T_TYPE_NUM_HAS_CHILD, pine, parent);
    else if (parent->left == NULL)
    {
        parent->left  = child;
        write_tree_logs (T_L_EDGE_SUC_CREATED, pine, parent);
        return parent->left;
    }
    write_tree_logs (T_FAIL_OF_CREATING_EDGE, pine);
    return NULL;
}

tree_node_t* tree_link_r (tree_t* pine, tree_node_t* parent, tree_node_t* child)
{
    MY_ASSERT (parent != NULL && child != NULL);
    if (parent->node_type == TYPE_NUM) write_tree_logs (T_TYPE_NUM_HAS_CHILD, pine, parent);
    else if (parent->right == NULL)
    {

        parent->right = child;
        write_tree_logs (T_R_EDGE_SUC_CREATED, pine, parent);
        return parent->right;
    }
    write_tree_logs (T_FAIL_OF_CREATING_EDGE, pine);
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
    return NULL;
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
    write_tree_logs (T_NODE_SUC_DELETED , pine, node);
    return node;
}

tree_node_t* tree_delete (tree_t* pine, tree_node_t* tree_root)
{
    if (tree_root == NULL) return NULL;
    if (tree_root->left != NULL)
    {
        tree_delete (pine, tree_root->left);
    }
    if (tree_root->right != NULL)
    {
        tree_delete (pine, tree_root->right);
    }
    free (tree_root);

    write_tree_logs (T_NODE_SUC_DELETED , pine, tree_root);
    if (tree_root == pine->root)
    {
        write_tree_logs (T_TREE_WAS_CLEARED, pine);
    }

    return NULL;
}




