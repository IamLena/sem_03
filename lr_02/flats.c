#include<stdio.h>
#include<string.h>
#include<stdbool.h>

#define OK 0;

#define ADRESS_LEN 50

int main(void)
{
    struct flat_t
    {
        unsigned short int id;
        char adress[ADRESS_LEN];
        float size;
        unsigned short int rooms;
        unsigned int price;
        union
        {
            struct
            {
                bool finished;
            }new_flat;
            struct
            {
                unsigned short int year;
                unsigned short int owners;
                unsigned short int dwellers;
                bool animal;
            }old_flat;
        }type;

    };

   // myflat.old_flat = {1990, 3, 4, 1};
    struct flat_t myflat = {};
    myflat = {0, "adress", 50.00, 3, 50000};
    //myflat.type.old_flat = {1990, 3, 4, 1};
    printf("%hu\n", myflat.type.old_flat.year);
    return OK;
}
