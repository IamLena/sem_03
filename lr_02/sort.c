#include "derectives.h"
#include "output.h"
#include "sort.h"

void print_keys (k_el *table, int length)
{
    printf("---------------------------\n");
    printf("| # | index|    price     |\n");
    printf("---------------------------\n");
    for (int i = 0; i < length; i ++)
    {
        printf("|%3d|%6d|%14d|\n", i+1, table[i].index, table[i].price);
    }
}

void swap (k_el *left, k_el *right)
{
    int tmp = left->index;
    left->index = right->index;
    right->index = tmp;

    tmp = left->price;
    left->price = right->price;
    right->price = tmp;
}

void swap_ft(ft**left, ft**right)
{
    ft*tmp = *left;
    *left = *right;
    *right = tmp;
}

void sort(ft** flats, int length)//price
{
    k_el table[length];
    for (int i = 0; i < length; i ++)
    {
        table[i].index = i;
        table[i].price = flats[i]->price;
    }
    for (int i = 0; i < length - 1; i ++)
        for (int j = 0; j < length - i - 1; j ++)
            if (table[j].price > table[j + 1].price)
                swap(table + j, table + j + 1);
    print_keys(table, length);
    print_head();
    for (int i = 0; i < length; i ++)
    {
        printf("%3d", i);
        print_line(*flats[table[i].index]);
    }
}

void sort_flats(ft**flats, int length)
{
    ft *data = malloc(length * sizeof(ft));
    if (!data)
    {
        printf("can not make a copy of the table\n");
        return;
    }
    for (int i = 0; i < length; i ++)
        data[i] = *flats[i];
    ft **ptrs = malloc(length * sizeof(ft*));
    if (!ptrs)
    {
        printf("can not make a copy of the table\n");
        return;
    }
    for (int i = 0; i < length; i++)
        ptrs[i] = &data[i];
    for(int i = 0; i < length - 1; i ++)
        for (int j = 0; j < length - 1 - i; j ++)
            if (ptrs[j]->price > ptrs[j + 1]->price)
                swap_ft(ptrs + j, ptrs + j + 1);
    print_table(ptrs, length);
    free(data);
    free(ptrs);
}

void sort_shaker(ft **flats, int length)
{
    k_el table[length];
    for (int i = 0; i < length; i ++)
    {
        table[i].index = i;
        table[i].price = flats[i]->price;
    }
    for (int i = 0; i < length - 1; i ++)
    {
        for (int j = 0; j < length - i - 1; j ++)
            if (table[j].price > table[j + 1].price)
                swap(table + j, table + j + 1);
        for (int k = length - i - 2; k > i; k --)
            if (table[k].price < table[k - 1].price)
                swap(table + k, table + k - 1);
    }
    print_keys(table, length);
    print_head();
    for (int i = 0; i < length; i ++)
    {
        printf("%3d", i);
        print_line(*flats[table[i].index]);
    }
}

void sort_flats_shaker(ft**flats, int length)
{
    ft *data = malloc(length * sizeof(ft));
    if (!data)
    {
        printf("can not make a copy of the table\n");
        return;
    }
    for (int i = 0; i < length; i ++)
        data[i] = *flats[i];
    ft **ptrs = malloc(length * sizeof(ft*));
    if (!ptrs)
    {
        printf("can not make a copy of the table\n");
        return;
    }
    for (int i = 0; i < length; i++)
        ptrs[i] = &data[i];
    for(int i = 0; i < length - 1; i ++)
    {
        for (int j = 0; j < length - 1 - i; j ++)
            if (ptrs[j]->price > ptrs[j + 1]->price)
                swap_ft(ptrs + j, ptrs + j + 1);
        for (int k = length - i - 2; k > i; k --)
            if (ptrs[k]->price < ptrs[k - 1]->price)
                swap_ft(ptrs + k, ptrs + k - 1);
    }
    print_table(ptrs, length);
    free(data);
    free(ptrs);
}
