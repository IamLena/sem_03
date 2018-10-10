#include "derectives.h"
#include "input.h"
#include "action.h"
#include "output.h"

void menu(void)
{
    printf("MENU\n");
    printf("6) Create a database\n");
    printf("1) Print table\n");// 40 элементов
    printf("2) Add an element\n");
    printf("3) Delete an element\n");
    printf("4) Search\n");//поиск информации по вариантному полю записи
    //Найти все вторичное 2-х комнатное жилье в указанном ценовом диапазоне без животных
    printf("5) Sort\n");//упорядочить по ключу 1 способ; 2 способ сортировки + время вывести
}
int main(void)
{
    ft**flats = NULL;
    bool yn = true;
    int rc;
    while (yn)
    {
        menu();
        int action = input_action();
        if (action == ACTION_1)
            printf("ACTION 1\n");
        else if (action == ACTION_2)
            printf("ACTION 2\n");
        else if (action == ACTION_3)
            printf("ACTION 3\n");
        else if (action == ACTION_4)
            printf("ACTION 4\n");
        else if (action == ACTION_5)
            printf("ACTION 5\n");
        else if (action == ACTION_6)
        {
            //ft**flats = NULL;
            int length = 0;
            flats = create(&length);
            if (flats)
            {
                printf("hey\n");
                //print_line(flats[0][0]);
                print_table(flats, length);
            }
            else
                printf("nope\n");
        }
        else
            printf("Invalid input\n");
        rc = IO_ERR;
        while (rc != OK)
            rc = input_bool(&yn, "Do you want to continue work? ");
    }
    return OK;
    free (flats[0]);
    free(flats);
}
