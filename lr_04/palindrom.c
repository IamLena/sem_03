#include "defines.h"

int fill_stack(stack_t s, char *str)
{
    int i = 0;
    while ((!(is_full(s))) && (str[i] != '\0'))
    {
        push(s, str[i]);
        i++;
    }
    return OK;
}

char *get_string(stack_t s)
{
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
