#define TEX_START_EQU  "\\begin{equation*}\n    "
#define TEX_ENDEQU     "\n\\end{equation*}\n\n"
#define TEX_START_DIF  "\\begin{equation*}\n    \\frac{d}{d%c} = ", dif_var

#define TEX_INSERT_PNG "\\begin{figure}[h!]\n"                            \
                        "        \\centering\n"                           \
                        "         \\includegraphics[scale=0.5]{%s}\n"     \
                        "\\end{figure}\n\n"                               \


//----------------------------------------------------------------------------------------------------------------------------------------

#define TEX_WRITE_L_SIDE                        \
        if (tree_node->left != NULL)            \
        {                                       \
            rec_level++;                        \
            fprintf (LATEX_FILE, "{");          \
            write_func_in_tex (tree_node->left, is_one_arg_func, dif_var);\
            fprintf (LATEX_FILE, "}");          \
            rec_level--;                        \
        }

#define TEX_WRITE_R_SIDE                        \
        if (tree_node->right != NULL)           \
        {                                       \
            rec_level++;                        \
            fprintf (LATEX_FILE, "{");          \
            write_func_in_tex(tree_node->right, is_one_arg_func, dif_var);\
            fprintf (LATEX_FILE, "}");          \
            rec_level--;                        \
        }

//----------------------------------------------------------------------------------------------------------------------------------------
