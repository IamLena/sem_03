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
