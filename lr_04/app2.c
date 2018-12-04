#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "stack.h"
#include "io.h"
#include "palindrom.h"

unsigned long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );
    return d;
}

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

int main(void)
{
    unsigned long t1, t2;

    char *string1 = input_string();
    char *string2;

    stack_t s;
    s = create();

    t1 = tick();
    fill_stack(s, string1);
    string2 = get_string(s);
    t2 = tick();
    if (strcmp(string1, string2) == 0)
        printf("it is a palindrom\n");
    else
        printf("it is not a palindrom\n");
    printf("time = %lu\n", t2 - t1);
    pop_print(s);

    destroy(s);
    free(string1);
    free(string2);
    return OK;
}
