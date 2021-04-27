#pragma once


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "error.h"

enum _TYPE {NUMBER,PLUS,MINUS,TIME,DIVIDE,LPARENTH,RPARENTH};

typedef enum _TYPE TYPE;

struct _tokens
{
    char* value;
    TYPE type;
};

typedef struct _tokens Tokens;

struct _list_tokens
{
    Tokens* elems;
    int size; // a negative size mean that an error had occured
};

typedef struct _list_tokens List_tokens;

/**
 * @brief
 *
 * @param from
 * @param input
 *
 * @return
 */
size_t getUntil(size_t from,char* input,Tokens* t);

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
List_tokens* get_tokens(char* input);


int control_parenthesis(char* input, size_t size);
