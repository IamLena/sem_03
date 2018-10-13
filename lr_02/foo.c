#include<stdio.h>
#include"derectives.h"
#include "output.h"

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
            if (code != 1)
            {
                printf("can not save\n");
                break;
            }
        }
        fclose(f);
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
        return 0;
    }
    else
    {
        printf("can not read\n");
        return IO_ERR;
    }
}

int main(void)
{
    ft* flats_ptr[5];
    ft flats_data[5];
    for (int i = 0; i < 5; i ++)
        flats_ptr[i] = &flats_data[i];
    print_table(flats_ptr, 5);
    FILE *f;
    save_table("res.txt", flats_ptr, 5);
    f = fopen("res.txt", "rb");
    flats_data[3].id = 555;
//    for (int i = 0; i < 5; i ++)
//        printf("read %d - %d\n",i, (int)fread(flats_ptr[i], sizeof(ft), 1, f));
//    print_table(flats_ptr, 5);
    int len = 4;
    ft ** flats = NULL;
    read_table("res.txt", &flats, &len);
    printf("INN MAIN\n");
    print_table(flats, len);
    fclose(f);
    return 0;
}
