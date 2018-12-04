#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "stack_list.h"

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

stack_t create_2(void)
{

    stack_t s = malloc(sizeof(struct stack_type));
    if (s)
        s->top = 0;
    return s;
}

void destroy_2(stack_t s)
{
    free(s);
}

bool is_empty_2(const stack_t s)
{
    return s->top == 0;
}
bool is_full_2(const stack_t s)
{
    return s->top >= STACK_SIZE;
}
int push_2(stack_t s, item_t i)
{
    if (is_full(s))
        return -1;
    s->content[(s->top)++] = i;
    return 0;
}
int pop_2(stack_t s, item_t *i)
{
    assert(i);
    if (is_empty(s))
        return -1;
    *i = s->content[--(s->top)];
    return 0;
}

void pop_print_2(stack_t s)
{
    char el;
    while(!is_empty(s))
    {
        pop(s, &el);
        printf("%c ", el);
    }
    printf("\n");
}
