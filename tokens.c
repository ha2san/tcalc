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

char* clean_from_space(char* input)
{
    size_t length = strlen(input);
    size_t new_length = 0;
    char* new_input = calloc(length+1,sizeof(char));
    for (size_t i = 0; i < length; ++i) {
        if(input[i] != ' '){
            new_input[new_length++] = input[i];
        }
    }
    new_input[new_length] = 0;
    new_input = realloc(new_input,sizeof(char)*(new_length+1));
    printf("%s\n",new_input);
    //free(input);
    return new_input;
}

List_tokens* get_tokens(char* _input)
{
    char* input = clean_from_space(_input);
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
        free(input);
        free(tokens_array);
        free_list_tokens(ltokens);
        fprintf(stderr,"Memory issue");
        return NULL;
    }
    tokens_array = temp; 
    ltokens->elems = tokens_array;
    ltokens->size = control_parenthesis(input,index);

    free(input);
    if(ltokens->size == ERR_PARENTHESIS ) {
        free_list_tokens(ltokens);
        fprintf(stderr,"Il y a une erreur avec les parenthèses\n");
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
                  t[index].type = NUMBER;
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

    }
    if(in != 0) {
        return ERR_PARENTHESIS;
    }
    return (int)size;
}
