#pragma once
#include "hashmap.h"

#define ERR_PARENTHESIS -1
#define ERR_BAD_START -2
#define ERR_LEFT_BEFORE_NUMBER -3
#define ERR_SYNTAX -4
#define ERR_EMPTY_PARENTHESIS -5
#define ERR_NUMBER_AFTER_NUMBER -6
#define ERR_UNKNOWN_SYMBOL -7
#define ERR_BAD_END -8

enum type {NUMBER,MODULO,PLUS,MINUS,TIME,DIVIDE,POWER,LPARENTH,RPARENTH,VARIABLE, UNKNOWN};

typedef enum type token_type;

typedef struct tokens Tokens;

typedef struct list_tokens List_tokens;

struct tokens {
    char* value;
    token_type type;
};

struct list_tokens {
    Tokens* elems;
    int size; // a negative size mean that an error had occured //finally thats not a good idea
    int error;
};

void print_token(Tokens t);

void print_list_tokens(List_tokens const* list);

/**
 * @brief get rid of two minus sign if they are ?collé?
 *
 * @param input sanitized input
 * @param first_time is it the first time that the function run for this value
 *
 * @return new string of the calculation
 */
char* minus_clean(char* input,int first_time);

/**
 * @brief given the string input give the list of tokens
 *
 * @param input string of the calculation
 * @param map list of variables
 *
 * @return list of tokens
 */
List_tokens* get_tokens(char* input,struct hashmap* map);

/**
 * @brief free the list of tokens
 *
 * @param list
 */
void free_list_tokens(List_tokens* list);

/**
 * @brief
 *
 * @param from
 * @param input
 * @param v_name
 *
 * @return
 */
size_t get_variable_end(size_t from,char* input,char* v_name);

/**
 * @brief
 *
 * @param index
 * @param from
 * @param input
 * @param t
 * @param map
 *
 * @return
 */
size_t getUntil(size_t index, size_t* from,char* input,Tokens* t, struct hashmap* map);

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
 * @brief return if the char c is a number
 *
 * @param c
 *
 * @return boolean value
 */
int isNumber(char c);

/**
 * @brief control of the parenthesis are OK in the input
 *
 * @param input string of calculation
 * @param error return if there is an error
 */
void control_parenthesis(char* input, int* error);

/**
 * @brief check the syntax of the input
 *
 * @param list_tokens list of tokens
 *
 * @return error value
 */
int syntax_checker(List_tokens const* list_tokens);

/**
 * @brief print for debug
 *
 * @param error
 */
void print_syntax_error(int error);
