#include "differentiator.h"

tree_node_t* dif_node (const tree_node_t* tree_node)
{
    switch (tree_node->node_type)
    {
        case TYPE_NUM:
            return tree_new_num_node (0);

        case CONST_EXP:
            return tree_new_num_node (0);

        case TYPE_VAR:
            return tree_new_num_node (1);

        case OP_ADD:
            return tree_add_node (dif_node (tree_node->left), dif_node (tree_node->right));

        case OP_SUB:
            return tree_sub_node (dif_node (tree_node->left), dif_node (tree_node->right));

        case OP_MUL:
        {
            return tree_add_node (tree_mul_node (dif_node (tree_node->left),  copy_node (tree_node->right)),
                                  tree_mul_node (dif_node (tree_node->right), copy_node (tree_node->left)));
        }
        case OP_DIV:
        {
            tree_node_t* numer = tree_sub_node (tree_mul_node (dif_node (tree_node->left),  copy_node (tree_node->right)),
                                                tree_mul_node (dif_node (tree_node->right), copy_node (tree_node->left)));
            tree_node_t* denom = tree_pow_node (copy_node (tree_node->right), tree_new_num_node (2));

            return tree_div_node (numer, denom);
        }
        case OP_LN:
        {
            if (tree_node->right->node_type == TYPE_NUM) return tree_new_num_node (0);

            return tree_mul_node (dif_node (tree_node->right), tree_div_node (tree_new_num_node (1), copy_node (tree_node->right)));
        }
        case OP_LOG:
        {
            if (tree_node->right->node_type == TYPE_NUM && tree_node->left->node_type == TYPE_NUM) return tree_new_num_node (0);

            tree_node_t* denom = tree_mul_node (copy_node (tree_node->right), tree_ln_node (copy_node (tree_node->left)));
            return tree_mul_node (dif_node (tree_node->right), tree_div_node (tree_new_num_node (1), denom));
        }
        case OP_SIN:
        {
            if (tree_node->right->node_type == TYPE_NUM) return tree_new_num_node (0);

            return tree_mul_node (dif_node (tree_node->right), tree_cos_node (copy_node (tree_node->right)));
        }
        case OP_COS:
        {
            if (tree_node->right->node_type == TYPE_NUM) return tree_new_num_node (0);

            tree_node_t* ex_der = tree_mul_node (tree_new_num_node (-1), tree_sin_node (copy_node (tree_node->right)));
            return tree_mul_node (ex_der, dif_node (tree_node->right));
        }
        case OP_TG:
        {
            if (tree_node->right->node_type == TYPE_NUM) return tree_new_num_node (0);

            tree_node_t* ex_der = tree_div_node (tree_new_num_node (1), tree_pow_node (tree_cos_node (copy_node (tree_node->right)), tree_new_num_node (2)));
            return tree_mul_node (dif_node (tree_node->right), ex_der);
        }
        case OP_CTG:
        {
            if (tree_node->right->node_type == TYPE_NUM) return tree_new_num_node (0);

            tree_node_t* ex_der = tree_mul_node (tree_new_num_node (-1), tree_div_node (tree_new_num_node (1),
                                  tree_pow_node (tree_sin_node (copy_node (tree_node->right)), tree_new_num_node (2))));

            return tree_mul_node (dif_node (tree_node->right), ex_der);
        }
        case OP_POW:
        {
            if (tree_node->right->node_type == TYPE_NUM && tree_node->left->node_type == TYPE_NUM) return tree_new_num_node (0);
            else if (tree_node->right->node_type == TYPE_NUM)
            {
                tree_node_t* power = tree_pow_node (copy_node (tree_node->left), tree_sub_node (copy_node (tree_node->right), tree_new_num_node (1)));
                return tree_mul_node (copy_node (tree_node->right), tree_mul_node (dif_node (tree_node->left), power));
            }
            else
            {
                tree_node_t* exp = tree_pow_node (tree_new_num_node (CONST_EXP), tree_mul_node (copy_node (tree_node->right),
                                                                                 tree_ln_node  (copy_node (tree_node->left))));

                tree_node_t* ln_dif = tree_mul_node (tree_div_node (tree_new_num_node (1), copy_node (tree_node->left)), dif_node (tree_node->left) );
                tree_node_t* in_der = tree_add_node (tree_mul_node (dif_node (tree_node->right), tree_ln_node (copy_node (tree_node->left))),
                                      tree_mul_node (ln_dif, copy_node (tree_node->right)));
                return tree_mul_node (exp, in_der);
            }
        }
    }
    write_tree_logs (T_UNSUPPORTED_OPER);
    return NULL;
}

tree_node_t* copy_node (const tree_node_t* tree_node)
{
    MY_ASSERT (tree_node != NULL)
    switch (tree_node->node_type)
    {
        case TYPE_NUM:
            return tree_new_num_node (tree_node->value);

        case CONST_EXP:
            return tree_new_num_node (tree_node->value);

        case TYPE_VAR:
            return tree_new_var_node (tree_node->node_type);

        case OP_ADD:
            return tree_add_node (copy_node (tree_node->left), copy_node (tree_node->right));

        case OP_SUB:
            return tree_sub_node (copy_node (tree_node->left), copy_node (tree_node->right));

        case OP_MUL:
            return tree_mul_node (copy_node (tree_node->left), copy_node (tree_node->right));

        case OP_DIV:
            return tree_div_node (copy_node (tree_node->left), copy_node (tree_node->right));

        case OP_POW:
            return tree_pow_node (copy_node (tree_node->left), copy_node (tree_node->right));

        case OP_LN:
            return tree_ln_node  (copy_node (tree_node->right));

        case OP_SIN:
            return tree_sin_node (copy_node (tree_node->right));

        case OP_COS:
            return tree_cos_node (copy_node (tree_node->right));

        case OP_TG:
            return tree_tg_node  (copy_node (tree_node->right));

        case OP_CTG:
            return tree_ctg_node (copy_node (tree_node->right));
    }
    printf ("not here");
    return NULL;
}

tree_node_t* simpl_node (tree_node_t* tree_node)
{
    int change_flag = 0;

    // if ((tree_node->node_type == OP_ADD || tree_node->node_type == OP_SUB) && (tree_node->right->value == 0 || tree_node->value == 0))
    // {
    //     if (tree_node->right->value == 0)
    //     {
    //         tree_delete (tree_node->right);
    //         tree_node->right = NULL;
    //     }
    //     else
    //     {
    //         tree_delete (tree_node->left);
    //         tree_node->left = NULL;
    //     }
    //     change_flag = 1;
    // }
    if (is_arithm_op (tree_node->left) && tree_node->left->right->node_type == TYPE_NUM && tree_node->left->left->node_type == TYPE_NUM)
    {
        int value = tree_eval (tree_node->left);
        tree_delete (tree_node->left);
        tree_node->left = NULL;
        tree_link_l (tree_node, tree_new_num_node (value));
        change_flag = 1;
    }

    if (is_arithm_op (tree_node->right) && tree_node->right->right->node_type == TYPE_NUM && tree_node->right->left->node_type == TYPE_NUM)
    {
        int value = tree_eval (tree_node->right);
        tree_delete (tree_node->right);
        tree_node->right = NULL;
        tree_link_r (tree_node, tree_new_num_node (value));
        change_flag = 1;
    }

    if (tree_node->left != NULL)
    {
        simpl_node (tree_node->left);
    }
    if (tree_node->right != NULL)
    {
        simpl_node (tree_node->right);
    }

    return tree_node;
}
