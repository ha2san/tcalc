#include "tcalc.h"

void help(void)
{
    printf("TCALC: terminal calculator\n"
            "USAGE: operation\n");
}

int main_calcul(char* input)
{
    List_tokens* tok = get_tokens(input);

    if(tok == NULL)  return ERROR;
    int error = syntax_checker(tok);
    if (error){
        free_list_tokens(tok);
        fprintf(stderr,"SYNTAX ERROR\n");
        print_syntax_error(error);
        return -1;
    }
    else{
        printf("%g\n",do_calculation(tok));
        free_list_tokens(tok);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    if(argc > 1) {
        if(!strcmp(argv[1],"-h") || !strcmp(argv[1],"--help")) {
            help();
            return 0;
        }

        int ret = main_calcul(argv[1]);

        if (ret != 0) return ret;

    } else {
        printf("write \"clear\" to clear the screen\n"
                "write \"q\" to exit\n");
        do {
            char input[MAX] = {0};
            printf("> ");
            size_t index = 0;
            do {
                input[index] = (char) getc(stdin);
                if(input[index] != ' ')  index++;
            } while(input[index-1] != '\n');
            if (index > 1){
                input[index-1] = 0;
                if(!strcmp(input,"q")) return 0;
                else if(!strcmp(input,"clear")) system("clear");
                else{
                    main_calcul(input);
                    //if(ret != 0) return ret;
                }
            }

        } while (1);
    }
    return 0;
}

