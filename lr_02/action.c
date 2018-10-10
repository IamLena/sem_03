#include"derectives.h"
#include"input.h"
#include"action.h"

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
