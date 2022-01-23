#pragma once
#include <stdlib.h>
#include <stdbool.h>

enum input {STDIN,ARGV};

/**
 * @brief get rid of space and return error if bad value in it
 *
 * @param input string given by the user
 * @param length length of the string
 * @param where from stdin or stdout
 *
 * @return new sanitized input or NULL if error
 */
char* sanitize_input(char* input,size_t length,enum input where);

/**
 * @brief print help
 */
void help(void);

/**
 * @brief run the program if the user gave an argument
 *
 * @param argv user argument
 *
 * @return value of the calculation
 */
double run_argument(const char* argv);


/**
 * @brief free the variables list
 *
 * @param item variable name
 * @param udata value
 *
 * @return
 */
bool map_free(const void *item, void *udata);


/**
 * @brief print the variable list
 *
 * @param item
 * @param udata
 *
 * @return
 */
bool show_map(const void *item, void *udata);

/**
 * @brief run the program as REPL
 *
 * @return
 */
int run_stdin(void);
