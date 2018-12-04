#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "stack.h"
#include "io.h"
#include "palindrom.h"

unsigned long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );
    return d;
}

int main(void)
{
    int rc;
    stack_t s;
    bool is_pal;
    unsigned long t1, t2;
    s = create();
    if (!s)
    {
        printf("can not make a stack\n");
        return MEM_ERR;
    }
    rc = input(s);
    if (rc == OVERFLOW)
        printf("Stack overflow\n");
    else if (rc == EMPTY)
        printf("Empty input\n");
    else
    {
        t1 = tick();
        is_pal = is_palindrom(s);
        t2 = tick();
        pop_print(s);
        //is_pal == 1 ? "true" : "false"
        printf("%s\n", (is_pal == 1 ? "true" : "false"));
        printf("time is %lu\n", t2 - t1);
    }
    destroy(s);
    printf("rc = %d\n", rc);
    return rc;
}
