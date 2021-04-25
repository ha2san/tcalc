#include "tokens.h"

Tokens* tokens(char* input)
{
    size_t input_length = strlen(input);
    char** tokens_array = calloc(sizeof(char*),input_length);
    size_t from = 0, until = 0, index = 0 ;

    while(until < input_length)
    {
        until = getUntil(from,input);
        size_t length = until - from;
        tokens_array[index] = calloc(sizeof(char),length);
        strncpy(tokens_array[index],input+from,length);
        from = until;
        index++;
    }

    Tokens* tokens = calloc(sizeof(Tokens),1);
    tokens_array = realloc(tokens_array,sizeof(char**)*index);
    tokens->elems = tokens_array;
    tokens->size = index;
    return tokens;
}


size_t getUntil(size_t from,char* input)
{
    size_t until = from+1;
    if(until == strlen(input))
    {
        return until;
    }
    else
    {
        switch (input[from])
        {
        case '(':
        case ')':
        case '+':
        case '*':
        case '/':
            return until;
            break;
        case '-':
            if(isNumber(input[from-1]) == 0 && input[from-1] != ')' )
            {
                return whileNumber(from,input);
            }
            else
            {
                return until;
            }
            break;
        default:
            return whileNumber(from,input);
        }
    }
}


size_t whileNumber(size_t from, char* input)
{
    size_t until = from+1;
    while (until <= strlen(input))
    {
        switch (input[until])
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            until++;
            break;
        default:
            return until;
        }
    }
    return until;
}

int isNumber(char c)
{
    if( c <= '9' && c>= '0')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
