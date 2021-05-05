#include "tcalc.h"

void help(void)
{
    printf("TCALC: terminal calculator\n"
            "USAGE: operation\n");
}

int main(int argc, char *argv[])
{
    if(argc > 1) {
        if(!strcmp(argv[1],"-h") || !strcmp(argv[1],"--help")) {
            help();
            return 0;
        }
        List_tokens* tok = get_tokens(*(argv+1));

        if(tok == NULL)  return ERROR;
        else  printf("%g\n",do_calculation(tok));

    } else {
        do {
            char input[100];
            printf("> ");
            size_t index = 0;
            do {
                input[index] = (char) getc(stdin);
                index++;
            } while(input[index-1] != '\n');
            input[index-1] = 0;
            if(!strcmp(input,"q")) return 0;
            List_tokens* tok = get_tokens(input);
            if(tok == NULL)  return ERROR;
            else  printf("%g\n",do_calculation(tok));
        } while (1);
    }
    return 0;
}

