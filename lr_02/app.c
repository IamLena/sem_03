#include "derectives.h"
#include "input.h"

void menu(void)
{
    printf("MENU\n");
    printf("1) Print table\n");// 40 элементов
    printf("2) Add an element\n");
    printf("3) Delete an element\n");
    printf("4) Search\n");//поиск информации по вариантному полю записи
    //Найти все вторичное 2-х комнатное жилье в указанном ценовом диапазоне без животных
    printf("5) Sort\n");//упорядочить по ключу 1 способ; 2 способ сортировки + время вывести
}
int main(void)
{
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
        else
            printf("Invalid input\n");
        rc = input_bool(&yn, "Do you want to continue work? ");
        if (rc == IO_ERR)
        {
            printf("invalid input\n");
            while (rc != OK)
                rc = input_bool(&yn, "Do you want to continue work? ");
        }
    }
}
