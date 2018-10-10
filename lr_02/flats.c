#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#include "add.c"
#include "types.h"

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
    bool yn = true;
    int rc;
    while (yn)
    {
        menu();
        rc = input_bool(&yn, "Do you want to continue work? ");
        if (rc == IO_ERR)
        {
            printf("invalid input\n");
            while (rc != OK)
                rc = input_bool(&yn, "Do you want to continue work? ");
        }
    }
}
