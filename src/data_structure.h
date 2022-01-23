#include "tokens.h"

#define MAX 2024

struct Stack {
    //Tokens tokens_list[MAX];
    Tokens* tokens_list;
    size_t size;
};

typedef struct Stack Stack;

/**
 * @brief
 *
 * @param size_t
 *
 * @return
 */
Stack* stack_init(size_t);

/**
 * @brief
 *
 * @param s
 */
void stack_free(Stack* s);

/**
 * @brief
 *
 * @param stack
 * @param tokens
 *
 * @return
 */
int push(Stack* stack, Tokens tokens);

/**
 * @brief
 *
 * @param stack
 *
 * @return
 */
Tokens pop(Stack* stack);

/**
 * @brief
 *
 * @param stack
 *
 * @return
 */
Tokens head(Stack const* stack);

/**
 * @brief
 *
 * @param stack
 *
 * @return
 */
int isEmpty(Stack const * stack);

/**
 * @brief
 *
 * @param s
 */
void print_stack(Stack const *s);
