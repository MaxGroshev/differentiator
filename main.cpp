#include "tree.h"
#include "brackets_func.h"

int main ()
{
    struct tree_t pine = {};
    constructor  (&pine);
    FILE* read_br = fopen ("brackets_seq.txt", "r");
    read_brackets (read_br, &pine);
    fclose (read_br);

//     double res = tree_eval (&pine, pine.root);
//     printf ("%lg", res);
//
    //write_brackets (&pine, pine.root);
    //int res = tree_eval (&pine, pine.root);
    //printf ("\n%d", res);

    graph_dump  (&pine);


    tree_delete (&pine, pine.root);
}
