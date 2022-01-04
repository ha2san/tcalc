#include "data_structure.h"
#include "stdlib.h"
#include "stdio.h"

Stack* stack_init(size_t size)
{
    Stack* stack = calloc(1,sizeof(Stack));
    stack->tokens_list = calloc(size,sizeof(Tokens));
    return stack;
}

void stack_free(Stack* s)
{
    if(s->tokens_list) free(s->tokens_list);
    if(s) free(s);
    s = NULL;
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
