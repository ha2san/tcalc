#include "tcalc.h"

void print_token(Tokens t)
{
    printf("%s -> %d\n",t.value,t.type);
}

void print_list_tokens(List_tokens const* list)
{
    printf("size = %d\n",list->size);
    for (int i = 0; i < list->size; ++i) {
        print_token(list->elems[i]);
    }
}

char* minus_clean(char* input,int first_time)
{
    size_t length = strlen(input);
    size_t new_length = length;
    char* input_clean = calloc(length+2,sizeof(char));
    int start_zero = 0;
    size_t j = 0, i = 0;
    for (; i < length; ++i,++j) {
        if(!start_zero && i == 0 && (input[i] == '+' || input[i] == '-' )) {
            start_zero = 1;
            input_clean[j] = '0';
            new_length++;
            i--;
        } else if(input[i] == '-' && input[i+1] == '-') {
            input_clean[j] = '+';
            new_length--;
            i++;
        } else {
            input_clean[j] = input[i];
        }
    }

    if(!first_time) free(input);

    if(length == new_length && !start_zero)
        return input_clean;
    else
        return minus_clean(input_clean,0);
}

List_tokens* get_tokens(char* input,struct hashmap* map)
{
    size_t input_length = strlen(input);
    Tokens* tokens_array = calloc(sizeof(Tokens),input_length);
    size_t from = 0, until = 0, index = 0 ;

    while(until < input_length) {
        until = getUntil(index,&from,input,tokens_array,map);
        size_t length = until - from;
        if(tokens_array[index].type != VARIABLE){
            tokens_array[index].value = calloc(sizeof(char),length+1);
            strncpy(tokens_array[index].value,input+from,length);
        }else tokens_array[index].type = NUMBER;
        from = until;
        index++;
    }

    List_tokens* ltokens = calloc(sizeof(List_tokens),1);
    Tokens* temp = realloc(tokens_array,sizeof(Tokens)*index);
    if(temp == NULL) {
        free(tokens_array);
        free_list_tokens(ltokens);
        fprintf(stderr,"Memory issue");
        return NULL;
    }
    tokens_array = temp;
    ltokens->elems = tokens_array;
    ltokens->size = (int)index;
    control_parenthesis(input,&ltokens->error);

    if(ltokens->error == ERR_PARENTHESIS ) {
        free_list_tokens(ltokens);
        fprintf(stderr,"Syntax Error (parenthesis)\n");
        return NULL;
    }

    return ltokens;
}


void free_list_tokens(List_tokens* list)
{
    if(list != NULL) {
        if(list->elems != NULL) {
            for (int i = 0; i < list->size; ++i) {
                free(list->elems[i].value);
            }
            free(list->elems);
        }
        free(list);
    }
}
size_t get_variable_end(size_t from,char* input,char* v_name)
{
    size_t j = 0;
    from++;//get rid of the $
    char c;
    while((c = *(input+from)) != 0 && c != '+' && c!= '%' && c != '(' && c!= ')' && c != '/' 
            && c!= '*' && c!= '^')
    {
        v_name[j++] = *(input+from);
        from++;
    }
    //possibe infinite loop check with input length
    //from++;
    return from;
}



size_t getUntil(size_t index, size_t* from,char* input,Tokens* t, struct hashmap* map)
{
    size_t until = (*from)+1;

    switch (input[*from]) {
        case '$':  
            t[index].type = VARIABLE;
            char* v_name = calloc(50,sizeof(char));
            size_t length = get_variable_end(*from,input,v_name);
            t[index].value = calloc(50,sizeof(char));
            struct mapping *m_value = hashmap_get(map,&(struct mapping){ .variable_name=v_name });
            if(m_value == NULL) {
                printf("value of %s unknown\n",v_name);
                printf("List of variables:\n");
                hashmap_scan(map,show_map,NULL);
                putchar('\n');
                t[index].type = UNKNOWN;
                free(t[index].value);
                free(v_name);
                return length;
            }   
            free(v_name);
            snprintf(t[index].value, 50, "%lf", m_value->value);
            return length;

        case '%': t[index].type = MODULO; return until;
        case '(': t[index].type = LPARENTH; return until;
        case ')': t[index].type = RPARENTH; return until;
        case '+': t[index].type = PLUS; return until;
        case '*': t[index].type = TIME; return until;
        case '^': t[index].type = POWER; return until;
        case '/': t[index].type = DIVIDE; return until;
        case '-':
                  t[index].type = MINUS;
                  if( (t[index-1].type != NUMBER && t[index-1].type != RPARENTH)
                          || index == 0) {
                      t[index].type = NUMBER;
                      return whileNumber(*from,input);
                  } else return until;

        default:
                  if(isNumber(input[*from])) {
                      t[index].type = NUMBER;
                      return whileNumber(*from,input);
                  } else {
                      t[index].type = UNKNOWN; return until;
                  }
    }

}


size_t whileNumber(size_t from, char* input)
{
    size_t until = from+1;
    int haveAPoint = 0;//how to handle multiple point => error ??
    while (until <= strlen(input)) {
        if(isNumber(input[until]) || (input[until] == '.' && haveAPoint == 0)) {
            if(input[until] == '.') haveAPoint = 1;
            until++;
        }        else return until;
    }
    return until;
}

int isNumber(char c)
{
    return c <= '9' && c >= '0';
}



void control_parenthesis(char* input, int* error)
{
    int in = 0;
    for (size_t i = 0; i < strlen(input); ++i) {
        if(input[i] == '(') {
            in++;
        } else if (input[i] == ')') {
            in--;
        }

        if(in < 0) *error = ERR_PARENTHESIS;

    }
    if(in != 0) {
        *error =  ERR_PARENTHESIS;
    }
}




int syntax_checker(List_tokens const* list_tokens)
{
    switch (list_tokens->elems[0].type) {
        case LPARENTH:
        case NUMBER:
        case VARIABLE:
            break;
        default: return ERR_BAD_START;
    }

    for (int i = 1; i < list_tokens->size; ++i) {
        TYPE before = list_tokens->elems[i-1].type;
        switch(list_tokens->elems[i].type) {
            case UNKNOWN: return ERR_UNKNOWN_SYMBOL;
            case NUMBER:
                          if(before == RPARENTH)
                              return ERR_LEFT_BEFORE_NUMBER;
                          if(before == NUMBER)
                              return ERR_NUMBER_AFTER_NUMBER;
                          break;
            case MODULO:
            case MINUS:
            case PLUS:
            case TIME:
            case DIVIDE:
            case POWER:
            case RPARENTH:
                          if(before != NUMBER && before != RPARENTH)
                              return ERR_SYNTAX;
                          break;
            case LPARENTH: if (before == RPARENTH)
                               return ERR_EMPTY_PARENTHESIS;
            //case VARIABLE:return ERR_UNKNOWN_SYMBOL;
        }
    }

    TYPE tp = list_tokens->elems[list_tokens->size-1].type;

    if(tp != NUMBER && tp != RPARENTH) {
        return ERR_BAD_END;
    }
    return EXIT_SUCCESS;
}

void print_syntax_error(int error)
{
    switch(error) {
        case ERR_SYNTAX:break;
        case ERR_EMPTY_PARENTHESIS: fprintf(stderr,"Parenthesis \")(\"\n"); break;
        case ERR_LEFT_BEFORE_NUMBER : fprintf(stderr,"Lefth parenthesis before a number\n"); break;
        case ERR_BAD_START: fprintf(stderr,"Bad start\n"); break;
        case ERR_NUMBER_AFTER_NUMBER: fprintf(stderr,"Number after another number\n"); break;
        case ERR_UNKNOWN_SYMBOL: fprintf(stderr,"Unknown symbol\n"); break;
        default:break;
    }
}
