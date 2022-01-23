#pragma once
#include "hashmap.h"
#include "tokens.h"


/**
 * @brief
 *
 * @param input
 * @param error_exit
 * @param map
 *
 * @return
 */
double main_calcul(char* input,int* error_exit,struct hashmap* map);

/**
 * @brief
 *
 * @param list_token
 *
 * @return
 */
double do_calculation(List_tokens* list_token);

/**
 * @brief
 *
 * @param list_token
 */
void tokens_to_postfix(List_tokens* list_token);

/**
 * @brief
 *
 * @param list_token
 *
 * @return
 */
double postfix_calculation(List_tokens* list_token);
