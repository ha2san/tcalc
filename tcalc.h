#include "tokens.h"
#include "error.h"

#define ERROR -1

typedef struct _tree Tree;

struct _tree
{
    Tokens value;
    Tree* left_tree;
    Tree* right_tree;
};

double do_calculation(List_tokens const* list);

Tree* tokens_to_tree(List_tokens const* list);

double tree_calculation(Tree* tree);
