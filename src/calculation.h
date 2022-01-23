#pragma once
#include "hashmap.h"
#include "tokens.h"


/**
 * @brief does the calcul and return the value
 *
 * @param input expression given by the user
 * @param error_exit to know if an error occured
 * @param map used for variables
 *
 * @return value of the calcul
 */
double main_calcul(char* input,int* error_exit,struct hashmap* map);

/**
 * @brief does the calculation given the tokens
 *
 * @param list_token list of tokens
 *
 * @return value of the calculation
 */
double do_calculation(List_tokens* list_token);

/**
 * @brief rearrange the order of the tokens to match a postfix order
 *
 * @param list_token list of tokens
 */
void tokens_to_postfix(List_tokens* list_token);

/**
 * @brief given a list of tokens in postfix order, does the calculation
 *
 * @param list_token list of tokens in postfix order
 *
 * @return value of the calculation
 */
double postfix_calculation(List_tokens* list_token);
