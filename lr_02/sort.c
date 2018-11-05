#include "derectives.h"
#include "output.h"
#include "sort.h"


/**
 * @brief make_keys формирование таблицы ключей
 * @param flats начало массива квартир
 * @param length длина таблицы
 * @return начало массива ключей
 * выделяем память под массив ключей той же длины, что и массив
 * если память выделить не получилось возвращаем ошибку, иначе
 * в цикле по элементам таблицы квартир копируем в элемент таблицы ключей значение индекса и цены
 */
k_el *make_keys(ft *flats, int length)
{
    k_el *table = malloc(length * sizeof(k_el));
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
ft *copy_table(ft *flats, int length)
{
    ft *data = malloc(length * sizeof(ft));
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
k_el *sort_keys(ft *flats, int length)//price
{
    k_el *table = make_keys(flats, length);
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
ft *sort_flats(ft *flats, int length)
{
    ft *data = copy_table(flats, length);
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

k_el *sort_keys_shaker(ft *flats, int length)
{
    k_el *table = make_keys(flats, length);
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

ft *sort_flats_shaker(ft *flats, int length)
{
    ft *data = copy_table(flats, length);
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
