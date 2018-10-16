#ifndef DERECTIVES_H
#define DERECTIVES_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
#include<math.h>

#define ADRESS_LEN 50
#define CHUNK 5

#define NEW 11
#define OLD 22

#define OK 101
#define IO_ERR 202
#define DEL_ERR 303

#define ACTION_1 1
#define ACTION_2 2
#define ACTION_3 3
#define ACTION_4 4
#define ACTION_5 5
#define ACTION_6 6
#define ACTION_7 7

struct type1{
    bool finished;
};

struct type2{
    short int year;
    short int owners;
    short int dwellers;
    bool animal;
};

struct flat_t
{
    unsigned short int id;
    char adress[ADRESS_LEN];
    float size;
    short int rooms;
    int price;
    bool is_new;
    union
    {
        struct type1 newflat;
        struct type2 oldflat;
    }type;

};

typedef struct flat_t ft;

#endif // DERECTIVES_H
