#include "derectives.h"
#include "output.h"
#include "sort.h"

unsigned long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );
    return d;
}

unsigned long average (unsigned long *t, int length)
{
    unsigned long sum = 0;
    for (int i = 0; i < length; i++)
        sum += t[i];
    return (sum / length);
}

/**
 * @brief make_keys формирование таблицы ключей
 * @param flats начало массива квартир
 * @param length длина таблицы
 * @return начало массива ключей
 * выделяем память под массив ключей той же длины, что и массив
 * если память выделить не получилось возвращаем ошибку, иначе
 * в цикле по элементам таблицы квартир копируем в элемент таблицы ключей значение индекса и цены
 */
k_el *make_keys(ft *flats, int length, unsigned long *t)
{
    unsigned long t1, t2;
    t1 =  tick();
    k_el *table = malloc(length * sizeof(k_el));
    t2 = tick();
    *t = t2 - t1;
    if (!table)
        return NULL;
    for (int i = 0; i < length; i ++)
    {
        table[i].index = i;
        table[i].price = flats[i].price;
    }
    return table;
}

/**
 * @brief copy_table копирует таблицу ключей
 * @param flats начало массива структур
 * @param length его длина
 * @return начало массива-копии
 */
ft *copy_table(ft *flats, int length, unsigned long *t)
{
    unsigned long t1, t2;
    t1 =  tick();
    ft *data = malloc(length * sizeof(ft));
    t2 = tick();
    *t = t2 - t1;
    if (!data)
    {
        printf("can not make a copy of the table\n");
        return NULL;
    }
    for (int i = 0; i < length; i++)
        data[i] = flats[i];
    return data;
}

/**
 * @brief sort_keys формирование и сортировка таблицы ключей
 * @param flats начало массива квартир
 * @param length длина таблицы
 * @return начало таблицы ключей
 */
k_el *sort_keys(ft *flats, int length, unsigned long *t)//price
{
    k_el *table = make_keys(flats, length, t);
    if (!table)
        return NULL;
    for (int i = 0; i < length - 1; i ++)
        for (int j = 0; j < length - i - 1; j ++)
            if (table[j].price > table[j + 1].price)
            {
                k_el tmp = table[j];
                table[j] = table[j + 1];
                table[j + 1] = tmp;
            }
    return table;
}

/**
 * @brief sort_flats формирование и сортировка таблицы
 * @param flats начало массива квартир
 * @param length длина таблицы
 * @return начало таблицы ключей
 */
ft *sort_flats(ft *flats, int length, unsigned long *t)
{
    ft *data = copy_table(flats, length, t);
    if (!data)
        return NULL;
    for (int i = 0; i < length - 1; i++)
    {
        for (int j = 0; j < length - i - 1; j++)
            if (data[j].price > data[j + 1].price)
            {
                ft tmp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = tmp;
            }
    }
    return data;
}

k_el *sort_keys_shaker(ft *flats, int length, unsigned long *t)
{
    k_el *table = make_keys(flats, length, t);
    if (!table)
        return NULL;
    for (int i = 0; i < length - 1; i ++)
    {
        for (int j = 0; j < length - i - 1; j ++)
            if (table[j].price > table[j + 1].price)
            {
                k_el tmp = table[j];
                table[j] = table[j + 1];
                table[j + 1] = tmp;
            }
        for (int k = length - i - 2; k > i; k --)
            if (table[k].price < table[k - 1].price)
            {
                k_el tmp = table[k];
                table[k] = table[k - 1];
                table[k - 1] = tmp;
            }
    }
    return table;
}

ft *sort_flats_shaker(ft *flats, int length, unsigned long *t)
{
    ft *data = copy_table(flats, length, t);
    if (!data)
        return NULL;
    for(int i = 0; i < length - 1; i ++)
    {
        for (int j = 0; j < length - 1 - i; j ++)
            if (data[j].price > data[j + 1].price)
            {
                ft tmp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = tmp;
            }
        for (int k = length - i - 2; k > i; k --)
            if (data[k].price < data[k - 1].price)
            {
                ft tmp = data[k];
                data[k] = data[k - 1];
                data[k - 1] = tmp;
            }
    }
    return data;
}
