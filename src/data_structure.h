#include "tokens.h"

#define MAX 2024

struct Stack {
    //Tokens tokens_list[MAX];
    Tokens* tokens_list;
    size_t size;
};

typedef struct Stack Stack;

/**
 * @brief init the stack in the heap, if the stack is not needed after the return of the function
 *        it's better to not used it and allocate the stack structure in the stack as it is faster
 *
 * @param size_t size of the stack
 *
 * @return return the address of the new allocated stack (NULL if error)
 */
Stack* stack_init(size_t);

/**
 * @brief free the stack that has been allocated in the heap
 *
 * @param s stack
 */
void stack_free(Stack* s);

/**
 * @brief push an element into the stack
 *
 * @param stack
 * @param tokens
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
int push(Stack* stack, Tokens tokens);

/**
 * @brief pop a value from the stack
 *
 * @param stack
 *
 * @return the value returned (NULL if empty)
 */
Tokens pop(Stack* stack);

/**
 * @brief return the head of the stack without poping it (peek)
 *
 * @param stack
 *
 * @return the value at the head
 */
Tokens head(Stack const* stack);

/**
 * @brief return if the stack is empty
 *
 * @param stack
 *
 * @return boolean value
 */
int isEmpty(Stack const * stack);

/**
 * @brief debug fonction
 *
 * @param s
 */
void print_stack(Stack const *s);
