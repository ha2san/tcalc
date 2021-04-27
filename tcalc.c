#include "tcalc.h"


int main(int argc, char *argv[])
{
    if(argc > 1)
    {
        List_tokens* tok = get_tokens(*(argv+1));

        if(tok == NULL)
        {
            return ERROR;
        }

    }
    else
    {
        char* input = calloc(sizeof(char),100);
        do
        {


            printf(">");
            size_t index = 0;

            do
            {
                input[index] = (char) getc(stdin);
                index++;
            }
            while(input[index-1] != '\n');

            input[index-1] = 0;

            printf("|%s|\n",input);

            List_tokens* tok = get_tokens(input);

            for (int i = 0; i < tok->size; ++i)
            {
                printf("%s -> %d\n",tok->elems[i].value,tok->elems[i].type);
            }

            if(tok == NULL)
            {
                return ERROR;
            }
            else
            {

            }
        }
        while(1);
        free(input);
    }
    return 0;
}



