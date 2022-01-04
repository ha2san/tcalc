#include "calculation.h"
#include "tokens.h"
#include "tcalc.h"
#include "data_structure.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define ERROR -1

int is_set_variable(char* input)
{
    if(!input) return 0;
    if(*input == '$'){
        while(*input != '=' && *(input) != 0) input++;
        return *input == '=';
    }else return 0;
}

char* get_variable_name(char* input)
{
    char variable_name[100];
    input++;
    size_t i = 0;

    while(*input != '=')
    {
        variable_name[i] = *input;
        i++;
        input++;
    }

    char* variable = calloc(i+2,sizeof(char));
    strncpy(variable,variable_name,i);
    return variable;
}

char* get_rid_variable(char* input)
{
    while(*input != '=') input++;
    input++;

    return input;
}

double main_calcul(char* input,int* error_exit,struct hashmap* map)
{
    char* input_clean = minus_clean(input,1);
    char* real_input = input_clean;
    char* variable_name = NULL;
    if(map && is_set_variable(input_clean)){
        variable_name = get_variable_name(input_clean);
        input_clean = get_rid_variable(input_clean);
    }
    List_tokens* tok = get_tokens(input_clean,map);


    free(real_input);


    if(tok == NULL)  return ERROR;
    int error = syntax_checker(tok);
    double ret = 0;
    if (error) {
        *error_exit = EXIT_FAILURE;
        fprintf(stderr,"SYNTAX ERROR\n");
        print_syntax_error(error);
    } else {
        *error_exit = EXIT_SUCCESS;
        ret = do_calculation(tok);
        if(map && variable_name){
            struct mapping* in_map = calloc(1,sizeof(struct mapping));
            in_map->variable_name = variable_name;
            in_map->value = ret;
            struct mapping* temp = hashmap_set(map,in_map);
            if(temp) {
                free(temp->variable_name);
            }
            free(in_map);
        }
    }

    free_list_tokens(tok);
    return ret;
}


double do_calculation(List_tokens* list_token)
{
    tokens_to_postfix(list_token);
    double ret = postfix_calculation(list_token);
    return ret;
}

int same_level(TYPE a,TYPE b)
{
    int ret = 0;
    switch (a) {
    case MODULO:
        if(b == MODULO) ret = 1;
        break;
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
    if(head(s2).type == LPARENTH) {
        Tokens tok = pop(s2);
        free(tok.value);
    }

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
    //Stack* output = stack_init((size_t)list_token->size);
    //Stack* memory = stack_init((size_t)list_token->size);
    Stack output;
    Stack memory;
    Tokens output_tokens[list_token->size];
    Tokens memory_tokens[list_token->size];
    output.tokens_list = output_tokens;
    memory.tokens_list = memory_tokens;
    output.size = 0;
    memory.size = 0;
    int new_size = 0;
    for (int i = 0; i < list_token->size; ++i) {
        switch (list_token->elems[i].type) {
        case NUMBER: push(&output,list_token->elems[i]); new_size++; break;
        case LPARENTH: push(&memory,list_token->elems[i]); break;
        case RPARENTH: stack_left_parenth(&output,&memory); free(list_token->elems[i].value); break;
        default: operand(&output,&memory,list_token->elems[i]); new_size++;
        }
    }

    while(!isEmpty(&memory)) {
        push(&output,pop(&memory));
    }



    list_token->size = new_size;
    list_token->elems = realloc(list_token->elems,(size_t)new_size*sizeof(Tokens));

    if(list_token->elems == NULL) {
        fprintf(stderr,"MEMORY ERROR");
        //stack_free(output);
        //stack_free(memory);
        return;
    }


    for (int i = list_token->size-1; i >= 0; --i) {
        list_token->elems[i] = pop(&output);
    }

    //stack_free(output);
    //stack_free(memory);
}
double modulo_calcul(double x, double y)
{
    int xInt = (int)x;
    int yInt = (int)y;
    if( fabs(xInt - x) > 0 ||fabs(yInt-y)> 0 )
        printf("(The result might not be true: The modulo operator must take INTEGER as operands)\n");
    return  xInt%yInt;
}
double calcul(double x, double y, TYPE t)
{
    switch (t) {
    case MODULO: return modulo_calcul(x,y);
    case PLUS: return x+y;
    case MINUS: return x-y;
    case TIME: return x*y;
    case DIVIDE: return x/y;
    case POWER : return pow(x,y);
    default: return 0;
    }
}

double postfix_calculation(List_tokens* list_token)
{
    double s[list_token->size];
    memset( s, 0,(size_t)(list_token->size)*sizeof(double) );
    size_t index = 0;
    for(int i = 0; i< list_token->size; i++) {
        if(list_token->elems[i].type == NUMBER) {
            s[index++] = atof(list_token->elems[i].value);
        } else {
            double y = s[--index];
            double x = s[--index];
            s[index++] = calcul(x,y,list_token->elems[i].type);
        }
    }
    return s[--index];
}
