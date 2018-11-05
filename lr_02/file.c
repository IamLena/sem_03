#include"derectives.h"
#include "input.h"
#include "output.h"
#include"file.h"

int save_table(char* filename, ft *flats, int length)
{
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
            code = (int)fwrite(flats + i, sizeof(ft), 1, f);
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

/**
 * @brief read_table читает таблицу из файла
 * @param filename строка-имя файла
 * @param flats - начало массива струкрут
 * @param length - длина
 * @return код ошибки
 * октрываем файл, не вышло - возвращаем ошибку.
 * если получилось открыть файл:
 * заводим новые локальные переменные
 * указатель на структуру - для переопределения памяти
 * реальную длину масива = 0, длину памяти выделенной, под массив = 0
 * code - который отвечает за удачное считывание из файла одной структуры = 1
 *
 * в цикле(пока успешно считан элемент из файла): если реальная длина массива равна количеству выделеной памяти, увеличиваем количество выделенной памяти.
 * Если переопределить массив в памяти не удалось, выходим из цикла, код ошибки равен ошибке памяти. считываем структуру из файла,
 * успешность этой опереции храним в предназначенной для этого переменной, увеличивает длину
 */
int read_table(char* filename, ft **flats, int *length)
{
    int rc = OK;
    FILE *f;
    f = fopen(filename, "rb");
    if (f)
    {
        ft *tmp_data = NULL;

        int rlen = 0;
        int mlen = 0;
        //int code = 1;

        ft *new_ft = malloc(sizeof(ft));
        if (!new_ft)
            return MEM_ERR;

        while (fread(new_ft, sizeof(ft), 1, f) == 1)
        {
            if (rlen == mlen)
            {
                mlen += CHUNK;
                {
                    ft* tmp = realloc(tmp_data, mlen * sizeof(ft));
                    if (tmp)
                        tmp_data = tmp;
                    else
                    {
                        printf("mem_err\n");
                        rc = MEM_ERR;
                        break;
                    }
                }
            }
            tmp_data[rlen] = *new_ft;
            rlen++;
        }
        free(new_ft);

//        while ( code == 1 )
//        {
//            if (rlen == mlen)
//            {
//                mlen += CHUNK;
//                {
//                    ft* tmp = realloc(tmp_data, mlen * sizeof(ft));
//                    if (tmp)
//                        tmp_data = tmp;
//                    else
//                    {
//                        printf("mem_err\n");
//                        rc = MEM_ERR;
//                        break;
//                    }
//                }
//            }
//            code = (int)fread(tmp_data + rlen, sizeof(ft), 1, f);
//            rlen ++;
//        }
//        rlen --;
//        ft* tmp = realloc(tmp_data, rlen * sizeof(ft));
//        if (tmp)
//            tmp_data = tmp;
//        else
//            printf("mem_err\n");
        *flats = tmp_data;
        *length = rlen;
        fclose(f);
        rc = OK;
    }
    else
    {
        printf("Can not read the table\n");
        rc = IO_ERR;
    }
    return rc;
}
