#ifndef SORT_H
#define SORT_H
#include "derectives.h"
void print_keys (k_el **table, int length);
void swap(k_el *left, k_el *right);
void swap_ft(ft**left, ft**right);
k_el **sort(ft** flats, int length);
ft **sort_flats(ft**flats, int length);
k_el **sort_shaker(ft** flats, int length);
ft **sort_flats_shaker(ft**flats, int length);

#endif // SORT_H
