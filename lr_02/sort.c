#include "derectives.h"
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
    print_keys(table, length);
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
    for(int i = 0; i < length - 1; i ++)
        for (int j = 0; j < length - 1 - i; j ++)
            if (flats[j]->price > flats[j + 1]->price)
                swap_ft(flats + j, flats + j + 1);
    print_table(flats, length);
}
