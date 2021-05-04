#include "tcalc.h"

double do_calculation(List_tokens const* list_token)
{
    Tree* tree = tokens_to_tree(list_token);
    double ret = tree_calculation(tree);
    return ret;
}

Tree* tokens_to_tree(List_tokens const* list_token)
{
    //TODO
    return NULL;
}

double tree_calculation(Tree* tree)
{
    //TODO
    return 0;
}
