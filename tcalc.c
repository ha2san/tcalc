#define _XOPEN_SOURCE 700
#include "tcalc.h"

void help(void)
{
    printf("TCALC: terminal calculator\n"
           "USAGE: operation\n");
}

char* minus_clean(char* input,int first_time)
{
    size_t length = strlen(input);
    size_t new_length = length;
    char* input_clean = calloc(length+1,sizeof(char));
    size_t j = 0, i = 0;
    for (;i < length; ++i,++j) {
       if(input[i] == '-' && input[i+1] == '-') {
            input_clean[j] = '+';
            new_length--;
            i++;
       }else{
           input_clean[j] = input[i];
       }
    }

    if(!first_time) free(input);

    if(length == new_length)
        return input_clean;
    else
        return minus_clean(input_clean,0);
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
               "write \"q\" to exit\n");
        char list_input[MAX][MAX];
        size_t list_size = 0;
        do {
            char input[MAX] = {0};
            printf("> ");
            size_t index = 0;

            do {
                input[index] = (char) getc(stdin);
                if(input[index] != ' ')  index++;
            } while(input[index-1] != '\n');

            input[index-1] = 0;
            if (index > 1) {
                if(!strcmp(input,"q")) return EXIT_SUCCESS;
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

