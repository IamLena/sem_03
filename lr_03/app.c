#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "error.h"
#include "io.h"
#include "mult.h"

int main(void)
{
    int rc = OK;

/* должно быть не тут
    //size
    int n, m;
    if ((input_int(&n, 5, "Input the quantity of rows:(0, 9999) ") != OK)
            || (input_int(&m, 5, "Input the quantity of columns:(0, 9999) ") != OK))
    {
        printf("Exiting the program");
        return IO_ERR;
    }
    printf("%d %d\n", n, m);*/

    char mode;
    mode:
    if (input_string(&mode, 2, "--------------------------\n1-file\n2-manual\n"
                     "3-auto(%)\nInput the mode of creation: ") != OK)
    {
        printf("Exiting the program");
        return IO_ERR;
    }
    if (mode - '0' == 1)
    {
        printf("working with file\n");
    }
    else if (mode - '0' == 2)
    {
        printf("manual input\n");
    }
    else if (mode - '0' == 3)
    {
        printf("auto percentage");
    }
    else
    {
        printf("Invalid input\n");
        int again = IO_ERR;
        bool yn;
        while (again != OK)
            again = input_bool(&yn, "Want to try again? ");
        if (yn == true)
            goto mode;
        if (yn == false)
        {
            printf("Exiting the program");
            return IO_ERR;
        }
    }

    return rc;
}
