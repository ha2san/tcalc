#pragma once

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct _tokens {
    char** elems;
    size_t size;
};

typedef struct _tokens Tokens;

/**
 * @brief 
 *
 * @param from
 * @param input
 *
 * @return 
 */
size_t getUntil(size_t from, char* input);

/**
 * @brief 
 *
 * @param from
 * @param input
 *
 * @return 
 */
size_t whileNumber(size_t from, char* input);

/**
 * @brief 
 *
 * @param c
 *
 * @return 
 */
int isNumber(char c);

/**
 * @brief 
 *
 * @param input
 *
 * @return 
 */
Tokens* tokens(char* input);


