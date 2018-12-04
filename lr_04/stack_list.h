#ifndef STACK_LIST_H
#define STACK_LIST_H
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "stack_list.h"
#define STACK_SIZE 10

typedef char item_t;
typedef struct stack_type_list* stack_t_list;

struct node
{
    item_t value;
    node *next;
};

struct stack_type_list
{
    node head;
    int top;
};

stack_t create_2(void);

void destroy_2(stack_t s);

bool is_empty_2(const stack_t s);
bool is_full_2(const stack_t s);

int push_2(stack_t s, item_t i);
int pop_2(stack_t s, item_t *i);

void pop_print_2(stack_t s);

#endif // STACK_LIST_H
