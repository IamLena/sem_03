#include"derectives.h"
#include"input.h"
#include"action.h"
#include"output.h"

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

int save(char* filename, ft** flats, int length)
{
    if(flats == NULL || length == 0)
        return IO_ERR;
    printf("saving\n");
    print_table(flats, length);
    FILE *f;
    f = fopen(filename, "wb");
    if (f)
    {
        for (int i = 0; i < length; i ++)
        {
            int code = fwrite(flats[i], sizeof(ft), 1, f);
            printf("%d\n", code);
        }
        return OK;
    }
    else
    {
        printf("Can not save.\n");
        return IO_ERR;
    }
}

int save_table(char* filename, ft**flats, int length)
{
    if (length == 0 || flats == NULL)
    {
        printf("wrong params\n");
        return IO_ERR;
    }
    FILE *f = fopen(filename, "wb");
    if (f)
    {
        int code;
        for (int i = 0; i < length; i ++)
        {
            code = (int)fwrite(flats[i], sizeof(ft), 1, f);
            printf("save %d - %d\n",i, code);
            if (code != 1)
            {
                printf("can not save\n");
                break;
            }
        }
        fclose(f);
        print_table(flats, length);
        return OK;
    }
    else
    {
        printf("can not read\n");
        return IO_ERR;
    }
}
int read_table(char* filename, ft***flats, int *length)
{
    FILE *f;
    f = fopen(filename, "rb");
    if (f)
    {
        ft** tmp_ptr = NULL;
        ft * tmp_data = NULL;
        int rlen = 0;
        int mlen = 0;
        int code = 1;
        while ( code == 1 )
        {
            if (rlen == mlen)
            {
                mlen += CHUNK;
                ft** tmp = realloc(tmp_ptr, mlen * sizeof(ft*));
                if (tmp)
                {
                    tmp_ptr = tmp;
                    ft* tmp = realloc(tmp_data, mlen * sizeof(ft));
                    if (tmp)
                        tmp_data = tmp;
                }
            }
            code = (int)fread(tmp_data + rlen, sizeof(ft), 1, f);
            tmp_ptr[rlen] = tmp_data + rlen;
            rlen ++;
        }
        rlen --;
        ft** tmp1 = realloc(tmp_ptr, rlen * sizeof(ft*));
        if (tmp1)
        {
            ft* tmp2 = realloc(tmp_data, rlen * sizeof(ft));
            if (tmp2)
            {
                tmp_ptr = tmp1;
                tmp_data = tmp2;
            }
        }
        *flats = tmp_ptr;
        fclose(f);
        return OK;
    }
    else
    {
        printf("Can not read the table\n");
        return IO_ERR;
    }
}
