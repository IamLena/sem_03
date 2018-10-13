#include "derectives.h"
#include "input.h"
#include "action.h"
#include "output.h"

void menu(void)
{
    printf("MENU\n");
    printf("1) Print table\n");// 40 элементов
    printf("2) Open a database\n");
    printf("2) Add an element\n");
    printf("3) Delete an element\n");
    printf("4) Search\n");//поиск информации по вариантному полю записи
    //Найти все вторичное 2-х комнатное жилье в указанном ценовом диапазоне без животных
    printf("5) Sort\n");//упорядочить по ключу 1 способ; 2 способ сортировки + время вывести
    printf("6) Create a database\n");
}
int main(void)
{
    ft**flats = NULL;
    int length = 0;
    bool yn = true;
    int rc;
    while (yn)
    {
        menu();
        int action = input_action();
        if (action == ACTION_1)
        {
            if (print_table(flats, length) == IO_ERR)
                printf("There is no data.\n");
        }
        else if (action == ACTION_2)
        {
            char* file = "";
            if (input_string(file, 20, "Input name of the file with table: ") == IO_ERR)
                printf("Invalid file name, can not open the table.\n");
            else
            {
                printf("your file is - %s\n", file);
                if (read_table(file, &flats, &length) == OK)
                    printf("Opened, you can proceed to work.\n");
            }
        }
        else if (action == ACTION_3)
            printf("ACTION 3\n");
        else if (action == ACTION_4)
        {
            read_table("res.txt", &flats, &length);
            print_table(flats, length);
        }
        else if (action == ACTION_5)
        {
            printf("action 5");
            //save("res.txt", flats, length);
        }
        else if (action == ACTION_6)
        {
            //ft**flats = NULL;
//            int length = 0;
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
    if (flats != NULL)
    {
        if (flats[0] != NULL)
            free (flats[0]);
        free(flats);
    }
}
