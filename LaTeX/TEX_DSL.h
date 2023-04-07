#define TEX_START_EQU "\\begin{equation*}\n    "
#define TEX_END_EQU   "\n\\end{equation*}\n\n"

//----------------------------------------------------------------------------------------------------------------------------------------

#define TEX_WRITE_L_SIDE                        \
        if (tree_node->left != NULL)            \
        {                                       \
            rec_level++;                        \
            fprintf (LATEX_FILE, "{");          \
            write_latex_log (tree_node->left);  \
            fprintf (LATEX_FILE, "}");          \
            rec_level--;                        \
        }

#define TEX_WRITE_R_SIDE                        \
        if (tree_node->right != NULL)           \
        {                                       \
            rec_level++;                        \
            fprintf (LATEX_FILE, "{");          \
            write_latex_log (tree_node->right); \
            fprintf (LATEX_FILE, "}");          \
            rec_level--;                        \
        }

//----------------------------------------------------------------------------------------------------------------------------------------
