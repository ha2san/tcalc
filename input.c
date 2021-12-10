#include "tcalc.h"

char* sanitize_input(char* input,size_t length,enum INPUT where)
{
    char* new_input = calloc(length+1,sizeof(char));
    size_t index = 0;
    for (size_t i = 0; i < length; ++i) {

        if(input[i] != ' ')
            new_input[index++] = input[i];
    }
    if(where == STDIN) free(input);
    return new_input;
}

