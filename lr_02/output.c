#include"derectives.h"
#include"output.h"

void print_line(struct flat_t flat)
{
    printf("|%6hu|%40s|%10.3f|%6hu|%10hd|", flat.id, flat.adress, flat.size, flat.rooms, flat.price);
    if (flat.is_new == true)
    {
        printf(" new|");
        if (flat.type.newflat.finished == true)
            printf("    finished|                                    |");
        else
            printf("not finished|                                    |");
    }
    else
    {
        printf(" old|            |%6hu|%6hu|%6hu|", flat.type.oldflat.year, flat.type.oldflat.owners, flat.type.oldflat.dwellers);
        if (flat.type.oldflat.animal == true)
            printf("   with animals|");
        else
            printf("without animals|");
    }
    printf("\n");
}

void print_head(void)
{
    printf("your table:\n");
    printf("------------------------------");
    printf("------------------------------");
    printf("------------------------------");
    printf("------------------------------");
    printf("-------------");
    printf("\n");
    printf(" # ");
    printf("|  id  |");
    printf("              adress                    ");
    printf("|  size    |");
    printf(" rooms");
    printf("|  price   |");
    printf("type|");
    printf("                                                 |");
    printf("\n");
    printf("------------------------------");
    printf("------------------------------");
    printf("------------------------------");
    printf("------------------------------");
    printf("-------------");
    printf("\n");
}
int print_table(struct flat_t**flats, int length)
{
    if(flats == NULL || length == 0)
        return IO_ERR;
    print_head();
    for (int i = 0; i < length; i ++)
    {
        printf("%3d", i + 1);
        print_line(*flats[i]);
    }
    return OK;
}
