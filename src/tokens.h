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

char* minus_clean(char* input,int first_time);
List_tokens* get_tokens(char* input,struct hashmap* map);
void free_list_tokens(List_tokens* list);
size_t get_variable_end(size_t from,char* input,char* v_name);
size_t getUntil(size_t index, size_t* from,char* input,Tokens* t, struct hashmap* map);
size_t whileNumber(size_t from, char* input);
int isNumber(char c);
void control_parenthesis(char* input, int* error);
int syntax_checker(List_tokens const* list_tokens);
void print_syntax_error(int error);
