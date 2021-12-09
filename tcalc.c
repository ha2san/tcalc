#define _XOPEN_SOURCE 700
#include "tcalc.h"

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
    if (error) {
        free_list_tokens(tok);
        fprintf(stderr,"SYNTAX ERROR\n");
        print_syntax_error(error);
        return -1;
    } else {
        printf("%g\n",do_calculation(tok));
        free_list_tokens(tok);
    }
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    if(argc > 1) {
        if(!strcmp(argv[1],"-h") || !strcmp(argv[1],"--help")) {
            help();
            return EXIT_SUCCESS;
        }

        int ret = main_calcul(argv[1]);

        if (ret != 0) return ret;

    } else {
        printf("write \"clear\" to clear the screen\n"
               "write \"q\" or \"exit\" to exit\n");
        char list_input[MAX][MAX];
        size_t list_size = 0;
        do {
            char input[MAX] = {0};
            printf("> ");
            size_t index = 0;

            do {
                input[index] = (char) getc(stdin);

                if(input[index] > 126 || input[index] < 0) {
                    fprintf(stderr,"Invalid character\n");
                    return -1;
                }

                if(input[index] != ' ')  index++;
                if(index >= MAX) printf("Too big\n");
            } while(input[index-1] != '\n' && input[index-1] && index < MAX);

            input[index-1] = 0;
            if (index > 1) {
                if(!strcmp(input,"q") || !strcmp(input,"exit")) return EXIT_SUCCESS;
                else if(!strcmp(input,"clear")) system("clear");
                else {
                    strcpy(list_input[list_size++],input);
                    main_calcul(input);
                }
            }

        } while (1);
    }
    return EXIT_SUCCESS;
}

