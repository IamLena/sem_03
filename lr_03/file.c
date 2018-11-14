#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "error.h"
#include "io.h"

int get_file(FILE *f)
{
    char filename[20];
    if (input_string(filename, 20, "Input the file name: ") == IO_ERR)
    {
        printf("can not open the file\n");
        return FILE_ERR;
    }
    f = fopen(filename, "r");
    if (f)
    {
        printf("opened\n");
        return OK;
    }
    printf("Can not open the file\n");
    int rc = FILE_ERR;
    bool yn;
    while (rc != OK)
        rc = input_bool(&yn, "Want to try again? ");
    if (yn == true)
        rc = get_file(f);
    if (yn == false)
        rc = FILE_ERR;
    return rc;
    return OK;
}
