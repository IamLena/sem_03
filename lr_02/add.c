#include "derectives.h"
#include "input.h"
#include "add.h"

int add_line(ft*flats, int length)
{
    int rc;
    printf("adding line\n");
    struct flat_t new;

    new.id = length;
    rc = input_string(new.adress, ADRESS_LEN, "Adress (<50 symbols): ");
    if (rc != OK)
        return IO_ERR;
    rc = input_float(&new.size, "Size (m^2): ");
    if (rc != OK)
        return rc;
    rc = input_si(&new.rooms, "How many rooms does it have? ");
    if (rc != OK)
        return rc;
    rc = input_int(&new.price, "What is the price of 1 sq.m? ");
    if (rc != OK)
        return rc;
    rc = input_bool(&new.is_new, "Is the flat new? ");
    if (rc == IO_ERR)
        return rc;
    if (new.is_new)
    {
        rc = input_bool(&new.type.newflat.finished, "Is it repaired? ");
        if (rc == IO_ERR)
            return rc;
    }
    else
    {
        rc = input_si(&new.type.oldflat.year, "When was it built? ");
        if (rc != OK)
            return rc;
        rc = input_si(&new.type.oldflat.owners, "How many people have owned it? ");
        if (rc != OK)
            return rc;
        rc = input_si(&new.type.oldflat.dwellers, "How many people lived here before? ");
        if (rc != OK)
            return rc;
        rc = input_bool(&new.type.oldflat.animal, "Were there any animals? ");
        if (rc == IO_ERR)
            return rc;
    }
    printf("%hu %s %.3f %hu %d ", new.id, new.adress, new.size, new.rooms, new.price);
    if (new.is_new == true)
    {
        printf("new ");
        if (new.type.newflat.finished == true)
            printf("finished ");
        else
            printf("not finished");
    }
    else
    {
        printf("old %hu %hu %hu ", new.type.oldflat.year, new.type.oldflat.owners, new.type.oldflat.dwellers);
        if (new.type.oldflat.animal == true)
            printf("with animals");
        else
            printf("without animals");
    }
    bool yn;
    rc = IO_ERR;
    while (rc != OK)
        rc = input_bool(&yn, "\nIs this element correct? Do you want to add it? ");
    if (yn == true)
    {
        *(flats + length) = new;
        printf("Added\n");
    }
    else
    {
        printf("The line isn't added.\n");
        rc = IO_ERR;
    }


    return rc;
}
ft** create(int* length)
{
    int rc;
    printf("CREATING A NEW TABLE\n");
    ft **flats = NULL;
    int real_length = 0;
    int memory_length = CHUNK;
    flats = malloc(memory_length * sizeof(ft*));
    if (!flats)
        printf("Memory error occured.\nCan not create a new database.");
    else
    {
        ft *data = NULL;
        data = malloc(CHUNK * sizeof(ft));
        if (!data)
        {
            free(flats);
            printf("Memory error occured.\nCan not create a new database.\n");
        }
        else
        {
            bool yn = true;
            while (yn)
            {
                rc = IO_ERR;
                while (rc != OK)
                    rc = input_bool(&yn, "Do you want to add an element? ");
                if (yn == true)
                {
                    flats[real_length] = &data[real_length];
                    if (add_line(data, real_length) == OK)
                    {
                        real_length ++;
                    }
                    if (real_length == memory_length)
                    {
                        memory_length += CHUNK;
                        ft** tmp1 = realloc(flats, memory_length * sizeof(ft*));
                        if (!tmp1)
                            printf("Memory error occured.\nCan not add any more elements\n.");
                        else
                        {
                            ft* tmp2 = realloc(data, memory_length * sizeof(ft));
                            if (!tmp2)
                            {
                                free(tmp1);
                                printf("Memory error occured.\nCan not add any more elements\n.");
                            }
                            else
                            {
                                flats = tmp1;
                                data = tmp2;
                            }
                        }
                    }
                }
                else
                {
                    ft **tmp1 = realloc(flats, real_length * sizeof(ft*));
                    if (tmp1)
                    {
                        ft* tmp2 = realloc(data, real_length * sizeof(ft));
                        if (!tmp2)
                            free(tmp1);
                        else
                        {
                            flats = tmp1;
                            data = tmp2;
                        }
                    }
                }
            }
        }
    }
    *length = real_length;
    return flats;
}
