#include "tcalc.h"

struct Stack {
    Tokens tokens_list[MAX];
    size_t size;
};

typedef struct Stack Stack;

/**
 * @brief
 *
 * @return
 */
Stack* stack_init(void);

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
