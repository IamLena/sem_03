#ifndef STACK_LIST_H
#define STACK_LIST_H


#include "defines.h"

typedef struct stack_list_type* stack_list_t;

struct node
{
    item_t value;
    struct node *next;
};

struct stack_list_type
{
    struct node *head;
    int top;
};

stack_list_t create2(void);
void destroy2(stack_list_t s);

bool is_empty2(const stack_list_t s);
bool is_full2(const stack_list_t s);
int push2(stack_list_t s, item_t i);
int pop2(stack_list_t s, item_t *i);

void pop_print2(stack_list_t s);

#endif // STACK_LIST_H
