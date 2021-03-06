#include "input.h"
#include "calculation.h"
#include <string.h>
#include "../libraries/linenoise.h"
#include "time.h"


char* sanitize_input(char* input,size_t length,enum input where)
{
    if(!input) return NULL;
    char* new_input = calloc(length+1,sizeof(char));
    size_t index = 0;
    for (size_t i = 0; i < length; ++i) {

        if(input[i] != ' ')
            new_input[index++] = input[i];
        if(input[i] < 0 || input[i] > 126) {
            free(new_input);
            new_input = NULL;
            if(where == STDIN) free(input);
            return NULL;
        }
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


double run_argument(const char* argv)
{
    if(!argv[0]) return EXIT_SUCCESS;
    else if(!strcmp(argv,"-h") || !strcmp(argv,"--help")) {
        help();
        return EXIT_SUCCESS;
    } else if(!strcmp(argv,"time")) {
        main_function();
        return EXIT_SUCCESS;
    }

    char* input = sanitize_input((char*)argv,strlen(argv),ARGV);

    if(!input) return EXIT_FAILURE;

    int error;
    double ret = main_calcul(input,&error,NULL);
    if(error == EXIT_FAILURE) {
        if(input) free(input);
        return error;
    }
    printf("%g\n",ret);

    if(input) free(input);

    return ret;
}


bool map_free(const void *item, void *udata)
{
    const struct mapping *user = item;
    free(user->variable_name);
    return true;
}

bool show_map(const void *item, void *udata)
{
    const struct mapping *user = item;
    printf("\t$%s => %g\n",user->variable_name,user->value);

    return true;
}


int run_stdin(void)
{
    printf("write \"clear\" to clear the screen\n"
           "write \"q\" or \"exit\" to exit\n");
    struct hashmap* map = new_map();

    linenoiseHistoryLoad("/tmp/history.txt"); /* Load the history at startup */


    while(1) {
        char* input = linenoise("> ");
        if(!input)
            continue;
        size_t length = strlen(input);
        input = sanitize_input(input,length,STDIN);


        if (input && length > 0) {
            linenoiseHistoryAdd(input); /* Add to the history. */
            linenoiseHistorySave("/tmp/history.txt"); /* Save the history on disk. */
            if(!strcmp(input,"q") || !strcmp(input,"exit") || !strcmp(input,"quit")) {
                linenoiseFree(input);
                input = NULL;
                break;
            } else if(!strcmp(input,"clear")) system("clear");
            else if(!strcmp(input,"time")) main_function();
            else if(!strcmp(input,"help")) help();
            else if(!strcmp(input,"variables")) hashmap_scan(map,show_map,NULL);
            else {
                int error;
                double calcul = main_calcul(input,&error,map);
                if(error == EXIT_SUCCESS) printf("%g\n",calcul);
            }
        }

        if(input)linenoiseFree(input);
        input = NULL;
    }

    hashmap_scan(map, map_free, NULL);
    hashmap_free(map);

    return EXIT_SUCCESS;
}

