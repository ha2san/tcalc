#pragma once

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define ERR_PARENTHESIS -1
#define ERROR -1
#define MAX 256
enum _TYPE {NUMBER,PLUS,MINUS,TIME,DIVIDE,POWER,LPARENTH,RPARENTH,END};

typedef enum _TYPE TYPE;

typedef struct _tokens Tokens;

typedef struct _list_tokens List_tokens;

struct _tokens {
    char* value;
    TYPE type;
};

struct _list_tokens {
    Tokens* elems;
    int size; // a negative size mean that an error had occured
};

void print_token(Tokens t);

void print_list_tokens(List_tokens const* list);

char* clean_from_space(char* input);

/**
 * @brief
 *
 * @param from
 * @param input
 *
 * @return
 */
size_t getUntil(size_t index, size_t* from,char* input,Tokens* t);

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

/**
 * @brief 
 *
 * @param list
 */
void free_list_tokens(List_tokens* list);


/**
 * @brief
 *
 * @param input
 * @param size
 *
 * @return
 */
int control_parenthesis(char* input, size_t size);

/**
 * @brief
 *
 * @param list
 *
 * @return
 */
double do_calculation(List_tokens* list);

/**
 * @brief
 *
 * @param list
 *
 * @return
 */
void tokens_to_postfix(List_tokens* list);

/**
 * @brief
 *
 * @param tree
 *
 * @return
 */
double postfix_calculation(List_tokens* list);
