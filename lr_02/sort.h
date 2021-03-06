#ifndef SORT_H
#define SORT_H
#include "derectives.h"

unsigned long tick(void);
unsigned long average (unsigned long *t, int length);
k_el *sort_keys(ft *flats, int length, unsigned long *t);
ft *sort_flats(ft *flats, int length, unsigned long *t);
k_el *sort_keys_shaker(ft *flats, int length, unsigned long *t);
ft *sort_flats_shaker(ft *flats, int length, unsigned long *t);

#endif // SORT_H
