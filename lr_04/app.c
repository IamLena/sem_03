#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "stack.h"
#include "io.h"

int main(void)
{
    char *string = input_string();
    if (!string)
        printf("can not read the string\n");
    if (string[0] == '\0')
        printf("empty input\ncan not proceed\n");

    printf("your string: ");
    puts(string);
    stack_t s;
    int rc;
    item_t i;
    s = create();
    if (!s)
    {
        free(string);
        printf("can not make a stack\n")
    }
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
