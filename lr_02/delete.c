#include "derectives.h"
#include "input.h"
#include "output.h"

int delete(ft **flats, int *length)
{
    if (flats == NULL || *flats == NULL || length == 0)
    {
        printf("nothing to delete. The table is empty\n");
        return DEL_ERR;
    }
    int index;
    int rc = OK;
    print_table(flats, *length);
    input_int(&index, "Input id of the element you want to delete: ");
    printf("the value is %d\n", index);
    if (index <= 0 || index > *length)
    {
        printf("Haven't found\n");
        rc = DEL_ERR;
    }
    else
    {
        print_line(*flats[index - 1]);
        if (index < *length)
        {
            print_line(*flats[index]);
            memmove(flats[index - 1], flats[index], (*length - index) * sizeof(ft));
        }
        *length -= 1;
//        free(flats[*length]);
//        flats[*length] = NULL;
        print_table(flats, *length);
    }
    return rc;
}
