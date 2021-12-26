#include "data_structure.h"

Stack* stack_init(void)
{
    Stack* stack = calloc(1,sizeof(Stack));
    return stack;
}

void stack_free(Stack* s)
{
    if(s != NULL) free(s);
}


int push(Stack* stack, Tokens tokens)
{
    if(stack->size >= MAX) return -1;
    else stack->tokens_list[stack->size++] = tokens;
    return EXIT_SUCCESS;
}

Tokens pop(Stack* stack)
{
    return stack->tokens_list[--(stack->size)];
}

Tokens head(Stack const* stack)
{
    return stack->tokens_list[stack->size-1];
}

int isEmpty(Stack const* stack)
{
    return stack->size <= 0;
}

void print_stack(Stack const* s)
{
    for (size_t i = 0; i < s->size; ++i) {
        printf("%s ",s->tokens_list[i].value);
    }
    putchar('\n');
}
