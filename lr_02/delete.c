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
    input_int(&index, "Input the number of the element you want to delete: ");
    printf("the value is %d\n", index);
    if (index <= 0 || index > *length)
    {
        printf("Haven't found\n");
        rc = DEL_ERR;
    }
    else
    {
        printf("this line \n");
        print_line(*flats[index - 1]);
        if (index < *length)
        {
            printf("replace with this\n");
            print_line(*flats[index]);
            printf("moving %d\n", (int)(*length - index));
            printf("moving %d\n", (int)((*length - index)*sizeof(ft)));
            memmove(flats[index - 1], flats[index], (*length - index) * sizeof(ft));
        }
        *length -= 1;
//        free(flats[*length]);
//        flats[*length] = NULL;
        printf("table in del\n");
        print_table(flats, *length + 1);
    }
    return rc;
}

int search(ft **flats, int length)//sorting price with keys
//Найти все вторичное 2-х комнатное жилье в указанном ценовом диапазоне без животных
{
    int lp, rp;
    if (input_int(&lp, "Input the lowest price: ") == IO_ERR)
        return IO_ERR;
    if (input_int(&rp, "Input the highest price: ") == IO_ERR)
        return IO_ERR;
    print_head();
    for (int i = 0; i < length; i ++)
    {
        if (flats[i]->rooms == 2 && flats[i]->type.oldflat.animal == false && flats[i]->is_new == false && flats[i]->price > lp && flats[i]->price < rp)
        {
            printf("%3d", i);
            print_line(*flats[i]);
        }
    }
    return OK;
}
