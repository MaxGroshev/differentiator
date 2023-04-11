#include "latex.h"

int latex_init (const char* tex_dir, int pattern)
{
    LATEX_FILE = fopen (tex_dir, "w");
    MY_ASSERT (LATEX_FILE != NULL);

    switch (pattern)
    {
        case TEX_DIF_PATTERN:
        read_pattern ("./LaTeX/tex_patterns/dif_pattern.tex");
        break;
    }
    return 0;
}

int read_pattern (const char* pat_dir)
{
    FILE* pat_file = fopen (pat_dir, "r");
    MY_ASSERT (pat_file != NULL);

    struct stat pat_file_data = {};
    stat (pat_dir, &pat_file_data);
    char* buffer = (char*) calloc (pat_file_data.st_size, sizeof (char));
    MY_ASSERT (buffer != NULL);

    fread  (buffer, sizeof (char), pat_file_data.st_size, pat_file);
    fwrite (buffer, sizeof (char), pat_file_data.st_size, LATEX_FILE);
    free   (buffer);
    fclose (pat_file);
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------

int write_latex_log (tree_node_t* tree_node, int equ_type, const char* text)
{
    MY_ASSERT (tree_node != NULL)

    static int rec_level = 0;
    if (rec_level == 0)
    {
        switch (equ_type)
        {
            case TEX_FUNCTION:
                fprintf (LATEX_FILE, "\\section{I am here to find you and I will...}");
                break;

            case TEX_DIF:
                fprintf (LATEX_FILE, "\\section{I did it... But at what cost}");
                break;

            case TEX_DIF_IN_POINT:
                fprintf (LATEX_FILE, "\\section{I found you exactly here}");
                break;

            case TEX_SIMPLIFIED:
                fprintf (LATEX_FILE, "\\section{So, Turbo-Mega ochev}");
                break;

            case TEX_RES:
                fprintf (LATEX_FILE, "\\section{The final trivial transition}");
                break;

        }
        if (text != NULL) fprintf (LATEX_FILE, "%s", text);
        fprintf (LATEX_FILE, TEX_START_EQU);
    }


    switch (tree_node->node_type)
    {
        case TYPE_NUM:
            fprintf (LATEX_FILE, "{");
            fprintf (LATEX_FILE, "%d", tree_node->value);
            fprintf (LATEX_FILE, "}");
            break;

        case CONST_EXP:
            fprintf (LATEX_FILE, "{");
            fprintf (LATEX_FILE, "e");
            fprintf (LATEX_FILE, "}");
            break;

        case TYPE_VAR:
            fprintf (LATEX_FILE, "{");
            fprintf (LATEX_FILE, "%c", tree_node->value);
            fprintf (LATEX_FILE, "}");
            break;

        case OP_ADD:
            fprintf (LATEX_FILE, "(");
            TEX_WRITE_L_SIDE;
            fprintf (LATEX_FILE, "+");
            TEX_WRITE_R_SIDE;
            fprintf (LATEX_FILE, ")");
            break;

        case OP_SUB:
            fprintf (LATEX_FILE, "(");
            TEX_WRITE_L_SIDE;
            fprintf (LATEX_FILE, "-");
            TEX_WRITE_R_SIDE;
            fprintf (LATEX_FILE, ")");
            break;

        case OP_MUL:
            TEX_WRITE_L_SIDE;
            fprintf (LATEX_FILE, "\\cdot");
            TEX_WRITE_R_SIDE;
            break;

        case OP_DIV:
            fprintf (LATEX_FILE, "\\frac");
            TEX_WRITE_L_SIDE;
            TEX_WRITE_R_SIDE;
            break;

        case OP_POW:
            TEX_WRITE_L_SIDE;
            fprintf (LATEX_FILE, "^");
            TEX_WRITE_R_SIDE;
            break;

        case OP_LN:
            fprintf (LATEX_FILE, "\\ln");
            fprintf (LATEX_FILE, "(");
            TEX_WRITE_R_SIDE;
            fprintf (LATEX_FILE, ")");
            break;

        case OP_LOG:
            fprintf (LATEX_FILE, "\\log");
            fprintf (LATEX_FILE, "_");
            TEX_WRITE_L_SIDE;
            TEX_WRITE_R_SIDE;
            break;

        case OP_SIN:
            fprintf (LATEX_FILE, "\\sin");
            fprintf (LATEX_FILE, "(");
            TEX_WRITE_R_SIDE;
            fprintf (LATEX_FILE, ")");
            break;

        case OP_COS:
            fprintf (LATEX_FILE, "\\cos");
            fprintf (LATEX_FILE, "(");
            TEX_WRITE_R_SIDE;
            fprintf (LATEX_FILE, ")");
            break;

        case OP_TG:
            fprintf (LATEX_FILE, "\\tg");
            fprintf (LATEX_FILE, "(");
            TEX_WRITE_R_SIDE;
            fprintf (LATEX_FILE, ")");
            break;

        case OP_CTG:
            fprintf (LATEX_FILE, "\\ctg");
            fprintf (LATEX_FILE, "(");
            TEX_WRITE_R_SIDE;
            fprintf (LATEX_FILE, ")");
            break;
    }

    if (rec_level == 0) fprintf (LATEX_FILE, TEX_ENEQU);
    return 0;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------------

int latex_distr ()
{
    fprintf (LATEX_FILE, "\\end {document}");
    fclose (LATEX_FILE);
    return 0;
}

