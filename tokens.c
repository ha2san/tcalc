#include "tcalc.h"

void print_token(Tokens t)
{
    printf("%s -> %d\n",t.value,t.type);
}

void print_list_tokens(List_tokens const* list)
{
    for (int i = 0; i < list->size; ++i) {
        print_token(list->elems[i]);
    }
}

List_tokens* get_tokens(char* input)
{
    size_t input_length = strlen(input);
    Tokens* tokens_array = calloc(sizeof(Tokens),input_length);
    size_t from = 0, until = 0, index = 0 ;

    while(until < input_length) {
        until = getUntil(&from,input,&tokens_array[index]);
        size_t length = until - from;
        tokens_array[index].value = calloc(sizeof(char),length+1);
        strncpy(tokens_array[index].value,input+from,length);
        from = until;
        index++;
    }

    List_tokens* ltokens = calloc(sizeof(List_tokens),1);
    tokens_array = realloc(tokens_array,sizeof(Tokens)*index);
    ltokens->elems = tokens_array;
    ltokens->size = control_parenthesis(input,index);

    if(ltokens->size == ERR_PARENTHESIS ) {
        fprintf(stderr,"Il y a une erreur avec les parenthèses\n");
        return NULL;
    }

    return ltokens;
}


void free_list_tokens(List_tokens* list)
{
    if(list != NULL){
        if(list->elems != NULL) free(list->elems);
        free(list);
    }
}

size_t getUntil(size_t* from,char* input,Tokens* t)
{
    size_t until = (*from)+1;

    switch (input[*from]) {
        case '(':
            t->type = LPARENTH; return until;
        case ')':
            t->type = RPARENTH; return until;
        case '+':
            t->type = PLUS; return until;
        case '*':
            t->type = TIME; return until;
        case '^':
            t->type = POWER; return until;
        case '/':
            t->type = DIVIDE; return until;
        case '-':
            t->type = MINUS;
            if((*from > 0 && isNumber(input[*from-1]) == 0 && input[*from-1] != ')' )
                    || *from == 0) {
                t->type = NUMBER;
                return whileNumber(*from,input);
            } else return until;

        case ' ':
            (*from)++;
            return getUntil(from,input,t);
        default:
            t->type = NUMBER;
            return whileNumber(*from,input);
    }

}


size_t whileNumber(size_t from, char* input)
{
    size_t until = from+1;
    int haveAPoint = 0;//how to handle multiple point => error ??
    while (until <= strlen(input)) {
        if(isNumber(input[until]) || (input[until] == '.' && haveAPoint == 0)){
            haveAPoint = 1;
            until++;
        }        else return until;
    }
    return until;
}

int isNumber(char c)
{
    if( c <= '9' && c>= '0') {
        return 1;
    } else {
        return 0;
    }
}



int control_parenthesis(char* input, size_t size)
{
    int in = 0;
    for (size_t i = 0; i < strlen(input); ++i) {
        if(input[i] == '(') {
            in++;
        } else if (input[i] == ')') {
            in--;
        }

    }
    if(in != 0) {
        return ERR_PARENTHESIS;
    }
    return (int)size;
}
