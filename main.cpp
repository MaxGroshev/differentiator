#include "brackets_func.h"

int main ()
{
    struct tree_t pine = {};
    constructor  (&pine);
    FILE* br_read = fopen ("./test_files/brackets_seq.txt", "r");
    read_brackets (br_read, &pine);
    fclose (br_read);

    double res = tree_eval (&pine, pine.root);
    printf ("%lg", res);

    write_brackets (&pine, pine.root);
    graph_dump  (&pine);

    tree_delete (&pine, pine.root);
}
