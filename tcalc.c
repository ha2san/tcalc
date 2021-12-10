#define _XOPEN_SOURCE 700
#include "tcalc.h"
#include <readline/readline.h>
#include <readline/history.h>

void help(void)
{
    printf("TCALC: terminal calculator\n"
           "usage:\n"
           "        $ tcalc \"3*(2+1)\"\n"
           "        9\n"
           "        or\n"
           "        $ tcalc\n"
           "        > 1.5*9.8+3.2\n"
           "        17.9\n\n"
           "operands: + - * ^\n");

}

int main_calcul(char* input)
{
    char* input_clean = minus_clean(input,1);
    List_tokens* tok = get_tokens(input_clean);
    free(input_clean);

    if(tok == NULL)  return ERROR;
    int error = syntax_checker(tok);
    int ret = EXIT_SUCCESS;
    if (error) {
        ret = EXIT_FAILURE;
        fprintf(stderr,"SYNTAX ERROR\n");
        print_syntax_error(error);
    } else {
        printf("%g\n",do_calculation(tok));
    }

    free_list_tokens(tok);
    return ret;
}

enum INPUT{STDIN,ARGV};

//TODO: put this function in another file
//      and do real work in it
char* sanitize_input(char* input,size_t length,enum INPUT where)
{
    //if STDIN free else do not free
    //get rid of space
    char* new_input = calloc(length+1,sizeof(char));
    size_t index = 0;
    for (size_t i = 0; i < length; ++i) {

        if(input[i] != ' ')
            new_input[index++] = input[i];
    }
    if(where == STDIN) free(input);
    return new_input;
}


int main(int argc, char *argv[])
{
    if(argc > 1) {
        if(!strcmp(argv[1],"-h") || !strcmp(argv[1],"--help")) {
            help();
            return EXIT_SUCCESS;
        }

        char* input = sanitize_input(argv[1],strlen(argv[1]),ARGV);

        int ret = main_calcul(input);

        free(input);

        if (ret != 0) return ret;

    } else {
        printf("write \"clear\" to clear the screen\n"
                "write \"q\" or \"exit\" to exit\n");
        using_history();
        while(1){
            char* input = readline("> ");
            if(!input)
                continue;
            size_t length = strlen(input);
            input = sanitize_input(input,length,STDIN);
            add_history(input);

            if (input && length > 0) {
                if(!strcmp(input,"q") || !strcmp(input,"exit")) {
                    free(input);
                    break;
                }
                else if(!strcmp(input,"clear")) system("clear");
                else {
                    main_calcul(input);
                }
            }

            free(input);
        }
    }
    return EXIT_SUCCESS;
}

