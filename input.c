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


int run_argument(const char* argv)
{
        if(!strcmp(argv,"-h") || !strcmp(argv,"--help")) {
            help();
            return EXIT_SUCCESS;
        }

        char* input = sanitize_input((char*)argv,strlen(argv),ARGV);

        int ret = main_calcul(input);

        free(input);

        if (ret != 0) return ret;

        return EXIT_SUCCESS;
}


int run_stdin(void)
{
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
        return EXIT_SUCCESS;
}

