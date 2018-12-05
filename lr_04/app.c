#include "defines.h"

unsigned long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );
    return d;
}

int main(void)
{
    unsigned long t1, t2;
    int rc;

    char *string1 = input_string();
    if (!string1)
    {
        printf("Memory error.");
        return MEM_ERR;
    }
    char *string2;

    stack_t s;
    s = create();
    if (!s)
    {
        printf("Memory error");
        return MEM_ERR;
    }

    t1 = tick();
    rc = fill_stack(s, string1);
    if (rc == OK)
    {
        string2 = get_string(s);
        if (string2)
        {
            t2 = tick();
            if (strcmp(string1, string2) == 0)
                printf("it is a palindrom\n");
            else
                printf("it is not a palindrom\n");
            printf("time = %lu\n", t2 - t1);
            pop_print(s);
            free(string2);
        }
        else
        {
            printf("Memory error\n");
            rc = MEM_ERR;
        }

    }
    else if (rc == EMPTY)
        printf("Empty input. Can not proceed.");
    else
        printf("Stack overflow. Try a shorter input.");

    destroy(s);
    free(string1);
    return OK;
}
