#pragma once
#include <stdlib.h>
#include <stdbool.h>

enum input {STDIN,ARGV};

/**
 * @brief
 *
 * @param input
 * @param length
 * @param where
 *
 * @return
 */
char* sanitize_input(char* input,size_t length,enum input where);

/**
 * @brief
 */
void help(void);

/**
 * @brief
 *
 * @param argv
 *
 * @return
 */
double run_argument(const char* argv);


/**
 * @brief
 *
 * @param item
 * @param udata
 *
 * @return
 */
bool map_free(const void *item, void *udata);


/**
 * @brief
 *
 * @param item
 * @param udata
 *
 * @return
 */
bool show_map(const void *item, void *udata);

/**
 * @brief
 *
 * @return
 */
int run_stdin(void);
