#include"derectives.h"
#include "input.h"
#include "output.h"
#include"file.h"

int save_table(char* filename, ft**flats, int length)
{
    print_table(flats, length);
    if (length == 0 || flats == NULL)
    {
        printf("Can not save an empty database\n");
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
        *length = rlen;
        fclose(f);
        return OK;
    }
    else
    {
        printf("Can not read the table\n");
        return IO_ERR;
    }
}
