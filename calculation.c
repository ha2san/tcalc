#include "tcalc.h"
#include "data_structure.h"

double do_calculation(List_tokens* list_token)
{
    tokens_to_postfix(list_token);
    putchar('\n');
    double ret = postfix_calculation(list_token);
    return ret;
}

int same_level(TYPE a,TYPE b)
{
    int ret = 0;
    switch (a) {
    case MINUS:
    case PLUS:
        if(b == MINUS || b == PLUS) ret = 1;
        break;
    case TIME:
    case DIVIDE:
        if(b == TIME || b == DIVIDE) ret =  1;
        break;
    default: ret = 0;
    }
    return ret;
}

void stack_left_parenth(Stack* s1, Stack* s2)
{
    while (!isEmpty(s2) && head(s2).type != LPARENTH) {
        push(s1,pop(s2));
    }
    if(head(s2).type == LPARENTH) pop(s2);
}



void operand(Stack* s1, Stack* s2, Tokens tok)
{
    if(isEmpty(s2) || head(s2).type == LPARENTH || (tok.type > head(s2).type && !same_level(head(s2).type,tok.type) )) {
        push(s2,tok);
    } else {
        push(s1,pop(s2));
        push(s2,tok);
    }
}

void tokens_to_postfix(List_tokens* list_token)
{
    Stack* output = stack_init();
    Stack* memory = stack_init();
    int new_size = 0;
    for (int i = 0; i < list_token->size; ++i) {
        switch (list_token->elems[i].type) {
        case NUMBER: push(output,list_token->elems[i]); new_size++; break;
        case LPARENTH: push(memory,list_token->elems[i]); break;
        case RPARENTH: stack_left_parenth(output,memory); break;
        default: operand(output,memory,list_token->elems[i]); new_size++;
        }
    }

    while(!isEmpty(memory)) {
        push(output,pop(memory));
    }

    print_stack(output);

    list_token->size =new_size;
    list_token->elems = realloc(list_token->elems,(size_t)new_size);

    for (int i = list_token->size-1; i >= 0; --i) {
        list_token->elems[i] = pop(output);
    }

    stack_free(output);
    stack_free(memory);
}

double postfix_calculation(List_tokens* list_token)
{
    //TODO
    return 0;
}
