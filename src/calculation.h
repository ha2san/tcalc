#pragma once
#include "hashmap.h"
#include "tokens.h"


double main_calcul(char* input,int* error_exit,struct hashmap* map);
double do_calculation(List_tokens* list_token);
void tokens_to_postfix(List_tokens* list_token);
double postfix_calculation(List_tokens* list_token);