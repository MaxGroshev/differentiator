#include "differentiator.h"

tree_node_t* dif_node (tree_t* dif_pine, const tree_node_t* tree_node)
{
    switch (tree_node->node_type)
    {
        case TYPE_NUM:
            return tree_new_num_node (dif_pine, 0);

        case TYPE_VAR:
            return tree_new_num_node (dif_pine, 1);

        case OP_ADD:
            return tree_add_node (dif_pine, dif_node (dif_pine, tree_node->left), dif_node (dif_pine, tree_node->right));

        case OP_SUB:
            return tree_sub_node (dif_pine, dif_node (dif_pine, tree_node->left), dif_node (dif_pine, tree_node->right));

        case OP_MUL:
        {
            return tree_add_node (dif_pine, tree_mul_node (dif_pine, dif_node (dif_pine, tree_node->left),  copy_node (dif_pine, tree_node->right)),
                                            tree_mul_node (dif_pine, dif_node (dif_pine, tree_node->right), copy_node (dif_pine, tree_node->left)));
        }
        case OP_DIV:
        {
            tree_node_t* numer = tree_sub_node (dif_pine, tree_mul_node (dif_pine, dif_node (dif_pine, tree_node->left),  copy_node (dif_pine, tree_node->right)),
                                                          tree_mul_node (dif_pine, dif_node (dif_pine, tree_node->right), copy_node (dif_pine, tree_node->left)));
            tree_node_t* denom = tree_pow_node (dif_pine, copy_node (dif_pine, tree_node->right), tree_new_num_node (dif_pine, 2));

            return tree_div_node (dif_pine, numer, denom);
        }
        case OP_LN:
        {
            if (tree_node->right->node_type == TYPE_NUM) return tree_new_num_node (dif_pine, 0);

            return tree_mul_node (dif_pine, dif_node (dif_pine, tree_node->right), tree_div_node (dif_pine, tree_new_num_node (dif_pine, 1),
                                                                                                 copy_node (dif_pine, tree_node->right)));
        }
        case OP_LOG:
        {
            if (tree_node->right->node_type == TYPE_NUM && tree_node->left->node_type == TYPE_NUM) return tree_new_num_node (dif_pine, 0);

            tree_node_t* denom = tree_mul_node (dif_pine, copy_node (dif_pine, tree_node->right), tree_ln_node (dif_pine, copy_node (dif_pine, tree_node->left)));
            return tree_mul_node (dif_pine, dif_node (dif_pine, tree_node->right), tree_div_node (dif_pine, tree_new_num_node (dif_pine, 1), denom));
        }
        case OP_SIN:
        {
            if (tree_node->right->node_type == TYPE_NUM) return tree_new_num_node (dif_pine, 0);

            return tree_mul_node (dif_pine, dif_node (dif_pine, tree_node->right), tree_cos_node (dif_pine, copy_node (dif_pine, tree_node->right)));
        }
        case OP_COS:
        {
            if (tree_node->right->node_type == TYPE_NUM) return tree_new_num_node (dif_pine, 0);

            tree_node_t* abs = tree_mul_node (dif_pine, dif_node (dif_pine, tree_node->right), tree_sin_node (dif_pine, copy_node (dif_pine, tree_node->right)));
            return tree_mul_node (dif_pine, tree_new_num_node (dif_pine, -1), abs);
        }
        case OP_TG:
        {
            if (tree_node->right->node_type == TYPE_NUM) return tree_new_num_node (dif_pine, 0);

            tree_node_t* ex_der = tree_div_node (dif_pine, tree_new_num_node (dif_pine, 1), tree_pow_node (dif_pine, tree_cos_node (dif_pine, copy_node (dif_pine, tree_node->right)),
                                                                                                                     tree_new_num_node (dif_pine, 2)));
            return tree_mul_node (dif_pine, dif_node (dif_pine, tree_node->right), ex_der);
        }
        case OP_CTG:
        {
            if (tree_node->right->node_type == TYPE_NUM) return tree_new_num_node (dif_pine, 0);

            tree_node_t* ex_der = tree_mul_node (dif_pine, tree_new_num_node (dif_pine, -1), tree_div_node (dif_pine, tree_new_num_node (dif_pine, 1),
                                  tree_pow_node (dif_pine, tree_sin_node (dif_pine, copy_node (dif_pine, tree_node->right)), tree_new_num_node (dif_pine, 2))));

            return tree_mul_node (dif_pine, dif_node (dif_pine, tree_node->right), ex_der);
        }
    }
    return NULL;
}

tree_node_t* copy_node (tree_t* dif_pine, const tree_node_t* tree_node)
{
    MY_ASSERT (tree_node != NULL && dif_pine != NULL)
    switch (tree_node->node_type)
    {
        case TYPE_NUM:
            return tree_new_num_node (dif_pine, tree_node->value);

        case TYPE_VAR:
            return tree_new_var_node (dif_pine, tree_node->node_type);

        case OP_ADD:
            return tree_add_node (dif_pine, copy_node (dif_pine, tree_node->left), copy_node (dif_pine, tree_node->right));

        case OP_SUB:
            return tree_sub_node (dif_pine, copy_node (dif_pine, tree_node->left), copy_node (dif_pine, tree_node->right));

        case OP_MUL:
            return tree_mul_node (dif_pine, copy_node (dif_pine, tree_node->left), copy_node (dif_pine, tree_node->right));

        case OP_DIV:
            return tree_div_node (dif_pine, copy_node (dif_pine, tree_node->left), copy_node (dif_pine, tree_node->right));

        case OP_POW:
            return tree_pow_node (dif_pine, copy_node (dif_pine, tree_node->left), copy_node (dif_pine, tree_node->right));

        case OP_LN:
            return tree_ln_node  (dif_pine, copy_node (dif_pine, tree_node->right));

        case OP_SIN:
            return tree_sin_node (dif_pine, copy_node (dif_pine, tree_node->right));

        case OP_COS:
            return tree_cos_node (dif_pine, copy_node (dif_pine, tree_node->right));

        case OP_TG:
            return tree_tg_node (dif_pine, copy_node (dif_pine, tree_node->right));

        case OP_CTG:
            return tree_ctg_node (dif_pine, copy_node (dif_pine, tree_node->right));
    }
    return NULL;
}
