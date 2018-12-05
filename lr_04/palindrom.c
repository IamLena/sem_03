#include "defines.h"

int fill_stack(stack_t s, char *str)
{
    assert(s);
    assert(str);
    int i = 0;
    while (str[i] != '\0')
    {
        if (is_full(s))
            return OVERFLOW;
        push(s, str[i]);
        i++;
    }
    if (i == 0)
        return EMPTY;
    return OK;
}

char *get_string(stack_t s)
{
    assert(s);
    char *string = malloc(STACK_SIZE + 1 * sizeof(item_t));
    if (string)
    {
        int i = 0;
        while(!is_empty(s))
        {
            pop(s, string + i);
            i++;
        }
        string[i] = '\0';
        puts(string);
    }
    return string;
}
