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

