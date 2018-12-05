#include "defines.h"

char *input_string(void)
{
    char *str = NULL;
    char c;
    char *tmp = NULL;
    int str_len = 0;
    int mem_len = 0;
    printf("input the string: ");
    while ((c = getchar()) && (c != EOF) && (c != '\n'))
    {
        printf("%c\n", c);
        if (str_len == mem_len)
        {
            mem_len += ADD_LENGTH;
            tmp = realloc(str, mem_len * sizeof(char));
            if (!tmp)
            {
                printf("null");
                if (str)
                    free(str);
                return NULL;
            }
            str = tmp;
        }
        str[str_len++] = c;
    }
    if (str_len == mem_len)
    {
        mem_len += ADD_LENGTH;
        tmp = realloc(str, mem_len * sizeof(char));
        if (!tmp)
        {
            if (str)
                free(str);
            return NULL;
        }
        str = tmp;
    }
    str[str_len++] = '\0';

    puts(str);
    return str;
}
