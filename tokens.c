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
        until = getUntil(index,&from,input,tokens_array);
        size_t length = until - from;
        tokens_array[index].value = calloc(sizeof(char),length+1);
        strncpy(tokens_array[index].value,input+from,length);
        from = until;
        index++;
    }

    List_tokens* ltokens = calloc(sizeof(List_tokens),1);
    Tokens* temp = realloc(tokens_array,sizeof(Tokens)*index);
    if(temp == NULL){
        free(tokens_array);
        free_list_tokens(ltokens);
        fprintf(stderr,"Memory issue");
        return NULL;
    }
    tokens_array = temp;
    ltokens->elems = tokens_array;
    ltokens->size = control_parenthesis(input,index);

    if(ltokens->size == ERR_PARENTHESIS ) {
        free_list_tokens(ltokens);
        fprintf(stderr,"Syntax Error (parenthesis)\n");
        return NULL;
    }

    return ltokens;
}


void free_list_tokens(List_tokens* list)
{
    if(list != NULL){
        if(list->elems != NULL){
            for (int i = 0; i < list->size; ++i) {
                free(list->elems[i].value);
            }
            free(list->elems);
        }
        free(list);
    }
}

size_t getUntil(size_t index, size_t* from,char* input,Tokens* t)
{
    size_t until = (*from)+1;

    switch (input[*from]) {
        case '(': t[index].type = LPARENTH; return until;
        case ')': t[index].type = RPARENTH; return until;
        case '+': t[index].type = PLUS; return until;
        case '*': t[index].type = TIME; return until;
        case '^': t[index].type = POWER; return until;
        case '/': t[index].type = DIVIDE; return until;
        case '-':
                  t[index].type = MINUS;
                  if( (index > 0 && t[index-1].type != NUMBER && t[index-1].type != RPARENTH)
                          || index == 0){
                      t[index].type = NUMBER;
                      return whileNumber(*from,input);
                  } else return until;

        default:
                  if(isNumber(input[*from])){
                      t[index].type = NUMBER;
                      return whileNumber(*from,input);
                  }else{
                      t[index].type = UNKNOWN; return until;
                  }
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
    return c <= '9' && c >= '0';
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

        if(in < 0) return ERR_PARENTHESIS;

    }
    if(in != 0) {
        return ERR_PARENTHESIS;
    }
    return (int)size;
}




int syntax_checker(List_tokens const* list)
{
    switch (list->elems[0].type) {
        case LPARENTH:
        case NUMBER:
            break;
        default: return ERR_BAD_START;
    }

    for (int i = 1; i < list->size; ++i) {
        TYPE before = list->elems[i-1].type;
        switch(list->elems[i].type){
            case UNKNOWN: return ERR_UNKNOWN_SYMBOL;
            case NUMBER:
                          if(before == RPARENTH) return ERR_LEFT_BEFORE_NUMBER;
                          if(before == NUMBER) return ERR_NUMBER_AFTER_NUMBER;
                          break;
            case MINUS:
            case PLUS:
            case TIME:
            case DIVIDE:
            case POWER:
            case RPARENTH:
                          if(before != NUMBER && before != RPARENTH)
                              return ERR_SYNTAX;
                          break;
            case LPARENTH: if (before == LPARENTH) return ERR_EMPTY_PARENTHESIS;
        }
    }
    return EXIT_SUCCESS;
}

void print_syntax_error(int error)
{
    switch(error){
        case ERR_SYNTAX:break;
        case ERR_EMPTY_PARENTHESIS: fprintf(stderr,"Parenthesis \")(\"\n");break;
        case ERR_LEFT_BEFORE_NUMBER : fprintf(stderr,"Lefth parenthesis before a number\n");break;
        case ERR_BAD_START: fprintf(stderr,"Bad start\n");break;
        case ERR_NUMBER_AFTER_NUMBER: fprintf(stderr,"Number after another number\n");break;
        case ERR_UNKNOWN_SYMBOL: fprintf(stderr,"Unknown symbol\n");break;
        default:break;
    }
}
