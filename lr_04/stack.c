#include "defines.h"

stack_t create(void)
{
    stack_t s = malloc(sizeof(struct stack_type));
    if (s)
        s->top = 0;
    return s;
}

void destroy(stack_t s)
{
    free(s);
}

bool is_empty(const stack_t s)
{
    return s->top == 0;
}
bool is_full(const stack_t s)
{
    return s->top >= STACK_SIZE;
}
int push(stack_t s, item_t i)
{
    if (is_full(s))
        return -1;
    s->content[(s->top)++] = i;
    return 0;
}
int pop(stack_t s, item_t *i)
{
    assert(i);
    if (is_empty(s))
        return -1;
    *i = s->content[--(s->top)];
    return 0;
}

void pop_print(stack_t s)
{
    char el;
    while(!is_empty(s))
    {
        pop(s, &el);
        printf("%c ", el);
    }
    printf("\n");
}
