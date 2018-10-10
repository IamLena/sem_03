#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#include "mytypes.h"

void print_line(struct flat_t flat)
{
    printf("%hu %s %f %hu %hd ", flat.id, flat.adress, flat.size, flat.rooms, flat.price);
    printf("\n");
}
