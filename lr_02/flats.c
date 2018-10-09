#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#include "add.c"
#include "types.h"

#define OK 0

#define ADRESS_LEN 50
#define CHUNK 5

void menu(void)
{
    printf("MENU\n");
    printf("1) Print table\n");
    printf("2) Add an element\n");
    printf("3) Delete an element\n");
    printf("4) Search\n");
    printf("5) Sort\n");
}
int main(void)
{
    menu();
//    struct flat_t* flats = NULL;
//    flats = malloc(CHUNK * sizeof(struct flat_t*));

//    struct flat_t * myflat2 = {
//        .id = 1,
//        .adress = "here",
//        .type.newflat.finished = true
//    };
//    printf("%s\n", myflat2.adress);
//    printf("%hu\n", myflat2.type.oldflat.dwellers);
    struct flat_t**flats = NULL;
    int length = 0;
    read("in.txt", flats, length);
    //print_line(flats[0]);
    return OK;
}
