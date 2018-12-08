#include "defines.h"
#include "stack_list.h"

stack_list_t create2(void)
{
    stack_list_t new = malloc(sizeof(struct stack_list_type));
    if (!new)
        return NULL;
    new->head = NULL;
    new->top = 0;
    return new;
}

void destroy2(stack_list_t s)
{
    struct node *next = s->head;
    while (next != NULL)
    {
        next = s->head->next;
        free(s->head);
    }
    s->head = NULL;
    s->top = 0;
}

bool is_empty2(const stack_list_t s)
{
    return s->top == 0;
}

bool is_full2(const stack_list_t s)
{
    return s->top >= STACK_SIZE;
}

int push2(stack_list_t s, item_t i)
{
    if (is_full2(s))
        return -1;

    struct node *new_head = malloc(sizeof(struct node));
    new_head->value = i;
    new_head->next = s->head;
    s->head = new_head;
    s->top++;
    return 0;
}

int pop2(stack_list_t s, item_t *i)
{
    if (is_empty2(s))
        return -1;
    struct node *tmp = s->head->next;
    *i = s->head->value;
    free(s->head);
    s->head = tmp;
    s->top--;
    return 0;
}

void pop_print2(stack_list_t s)
{
    struct node *cur = s->head;
    while (cur != NULL)
    {
        printf("%d ", cur->value);
        cur = cur->next;
    }
    printf("\n");
}
