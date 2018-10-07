#ifndef TYPES_H
#define TYPES_H

typedef struct flat_type
{
    unsigned short int id;
    char adress[ADRESS_LEN];
    float size;
    unsigned short int rooms;
    unsigned int price;
    union
    {
        struct new
        {
            bool finished;
        };
        struct old
        {
            unsigned short int year;
            unsigned short int owners;
            unsigned short int dwellers;
            bool animal;
        };

    };

} flat_t;
#endif // TYPES_H
