#include "tcalc.h"



Tokens* token_to_input(char* input)
{
    Tokens* toks = get_tokens(input);
    if(toks->size == ERR_PARENTHESIS)
    {
        fprintf(stderr,"Il y a un problème avec les parenthèses\n");
        return NULL;
    }
    else
    {
        return toks;
    }

}

int main(int argc, char *argv[])
{
    if(argc > 1)
    {
        Tokens* tok = token_to_input(*(argv+1));

        if(tok == NULL)
        {
            return ERROR;
        }

    }
    else
    {
        do
        {


            printf(">");
            char chaine[100];
            scanf("%[ˆ\n]", chaine);

            Tokens* tok = token_to_input(chaine);

            if(tok == NULL)
            {
                return ERROR;
            }
        }
        while(1);
    }
    return 0;
}



