int delete(ft ***flats, int *length)
{
    if (flats == NULL || *flats == NULL || length == 0)
    {
        printf("nothing to delete. The table is empty\n");
        return DEL_ERR;
    }
    int id;
    int rc = OK;
    print_table(*flats, *length);
    input_int(&id, "Input id of the element you want to delete: ");
    printf("the value is %d\n", id);
    if (id < 0 || id >= *length)
    {
        printf("Haven't found\n");
        rc = DEL_ERR;
    }
    else
    {
        printf("%d\n", *length);
        print_table(*flats, *length);
//        ft some = **flats[1];
//        printf("%s\n", some.adress);
        for (int i = 0; i < *length; i ++)
        {
            printf("%d\n",i);
            ft *some = *flats[i];
            printf("%s\n", some->adress);
        }
        if (id != *length - 1)
        {
            memmove(*flats[id], *flats[id + 1], (*length - 1 - id));
            printf("kyky\n");
            print_table(*flats, *length - 1);
        }
        ft ** tmp = realloc(*flats, (*length - 1) * sizeof(ft*));
        ft *tmp_data = realloc(*flats[0], (*length - 1) * sizeof(ft));
        if (tmp && tmp_data)
        {
            printf("hey\n");
            *length -= 1;
            *flats = tmp;
            for (int i = 0; i < *length; i ++)
                *flats[i] = &tmp_data[i];
            printf("done\n");
        }
        else
        {
            printf("can not delete\n");
            rc = DEL_ERR;
        }
    }
    return rc;
}
