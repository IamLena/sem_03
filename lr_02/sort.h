#ifndef SORT_H
#define SORT_H
#include "derectives.h"
void print_keys (k_el *table, int length);
void swap(k_el *left, k_el *right);
void swap_ft(ft**left, ft**right);
void sort(ft** flats, int length);
void sort_flats(ft**flats, int length);
void sort_shaker(ft** flats, int length);
void sort_flats_shaker(ft**flats, int length);

#endif // SORT_H
