#ifndef TYPES_H
#define TYPES_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define ADRESS_LEN 50

struct type1{
    bool finished;
};

struct type2{
    unsigned short int year;
    unsigned short int owners;
    unsigned short int dwellers;
    bool animal;
};

struct flat_t
{
    unsigned short int id;
    char adress[ADRESS_LEN];
    float size;
    unsigned short int rooms;
    unsigned int price;
    bool is_new;
    union
    {
        struct type1 newflat;
        struct type2 oldflat;
    }type;

};

#endif // TYPES_H
