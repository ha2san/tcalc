#pragma once

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "hashmap.h"


#define ERROR -1
#define MAX 2024
#define ERR_PARENTHESIS -1
#define ERR_BAD_START -2
#define ERR_LEFT_BEFORE_NUMBER -3
#define ERR_SYNTAX -4
#define ERR_EMPTY_PARENTHESIS -5
#define ERR_NUMBER_AFTER_NUMBER -6
#define ERR_UNKNOWN_SYMBOL -7
#define ERR_BAD_END -8


enum TYPE {NUMBER,MODULO,PLUS,MINUS,TIME,DIVIDE,POWER,LPARENTH,RPARENTH,VARIABLE, UNKNOWN};

enum INPUT {STDIN,ARGV};

typedef enum TYPE TYPE;

typedef struct tokens Tokens;

typedef struct list_tokens List_tokens;

struct tokens {
    char* value;
    TYPE type;
};


struct list_tokens {
    Tokens* elems;
    int size; // a negative size mean that an error had occured //finally thats not a good idea
    int error;
};

double main_calcul(char* input, int* error,struct hashmap*);

char* sanitize_input(char* input, size_t length, enum INPUT where);

double run_argument(const char*);

bool show_map(const void *item, void *udata);

int run_stdin(void);

/**
 * @brief
 *
 * @param t
 */
void print_token(Tokens t);

/**
 * @brief
 *
 * @param list
 */
void print_list_tokens(List_tokens const* list);


/**
 * @brief
 *
 * @param from
 * @param input
 *
 * @return
 */
size_t getUntil(size_t index, size_t* from,char* input,Tokens* t,struct hashmap*);

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
List_tokens* get_tokens(char* input,struct hashmap*);


/**
 * @brief
 *
 * @param list
 *
 * @return
 */
int syntax_checker(List_tokens const* list);

void print_syntax_error(int error);
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
void control_parenthesis(char* input, int* error);

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


char* minus_clean(char* input,int first_time);
