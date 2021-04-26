#pragma once


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "error.h"

struct _tokens
{
    char** elems;
    int size; // a negative size mean that an error had occured
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
Tokens* get_tokens(char* input);


int control_parenthesis(char* input, size_t size);
