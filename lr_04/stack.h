#ifndef STACK_H
#define STACK_H

#include "defines.h"

#define STACK_SIZE 10

typedef char item_t;
typedef struct stack_type* stack_t;

struct stack_type
{
    item_t content[STACK_SIZE];
    int top;
};

stack_t create(void);
void destroy(stack_t s);

bool is_empty(const stack_t s);
bool is_full(const stack_t s);
int push(stack_t s, item_t i);
int pop(stack_t s, item_t *i);

void pop_print(stack_t s);

#endif // STACK_H
