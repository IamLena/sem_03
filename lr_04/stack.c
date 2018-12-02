#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define STACK_SIZE 10

typedef int item_t;
typedef struct stack_type* stack_t;

struct stack_type
{
    item_t content[STACK_SIZE];
    item_t top;
};

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

int main(void)
{
    stack_t s;
    int rc;
    item_t i;
    s = create();
    assert(s); //NULL - не создалось
    i = 0;
    while (!is_full(s))
    {
        rc = push(s, i);
        i++;
    }
    while(!is_empty(s))
    {
        rc = pop(s, &i);
        printf("%d\n", i);
    }
    destroy(s);
    printf("rc = %d\n", rc);
    return 0;
}
