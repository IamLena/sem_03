#include <assert.h>
#include <stdbool.h>
#include "stack.h"
#include "palindrom.h"

bool compare (stack_t s1, stack_t s2)
{
    item_t el1, el2;

    assert(s1);
    assert(s2);
    //if (is_empty())
    if (s1->top - s2->top == 1)
        pop(s1, &el1);
    else if (s1->top - s2->top == -1)
        pop(s2, &el1);
    while ((!(is_empty(s1))) && (!(is_empty(s2))))
    {
        pop(s1, &el1);
        pop(s2, &el2);
        if (el1 != el2)
            return false;
    }
    return true;
}

bool is_palindrom(stack_t s)
{
    printf("length = %d\n", s->top);
    return true;
}
