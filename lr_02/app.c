#include "derectives.h"
#include "input.h"
#include "action.h"
#include "output.h"
#include "delete.h"

void menu(void)
{
    printf("MENU\n");
    printf("1) Print table\n");// 40 элементов
    printf("2) Open a database\n");
    printf("3) Create a new database\n");
    printf("4) Add an element\n");
    printf("5) Save the table\n");
    printf("6) Delete an element\n");
    printf("7) Search\n");//поиск информации по вариантному полю записи
    //Найти все вторичное 2-х комнатное жилье в указанном ценовом диапазоне без животных
    printf("8) Sort\n");//упорядочить по ключу 1 способ; 2 способ сортировки + время вывести
    printf("9) Create a database\n");
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
        int action = input_action();//print
        if (action == ACTION_1)
        {
            if (print_table(flats, length) == IO_ERR)
                printf("There is no data.\n");
        }
        else if (action == ACTION_2)//open
        {
            if (flats != NULL)
            {
                printf("Your existing table can be deleted.\nMake sure you have saved it.\n");
                bool yn;
                int code = 1;
                while (code != OK)
                {
                    code = input_bool(&yn, "Do you want to save it now? ");
                    if (yn == true)
                    {
                        char file[20];
                        if (input_string(file, 20, "Input name of the file with table: ") == IO_ERR)
                            printf("Invalid file name, can not open the table.\n");
                        else
                        {
                            printf("your file is - %s\n", file);
                            if (save_table(file, flats, length) == OK)
                                printf("Saved.\n");
                        }
                    }
                }
            }
            printf("OPENING TABLE\n");
            char file[20];
            if (input_string(file, 20, "Input name of the file with table: ") == IO_ERR)
                printf("Invalid file name, can not open the table.\n");
            else
            {
                printf("your file is - %s\n", file);
                if (read_table(file, &flats, &length) == OK)
                    printf("Opened, you can proceed to work.\n");
            }
        }
        else if (action == ACTION_3)//create
        {
            if (flats != NULL)
            {
                printf("Your existing table can be deleted.\nMake sure you have saved it.\n");
                bool yn;
                int code = 1;
                while (code != OK)
                {
                    code = input_bool(&yn, "Do you want to save it now? ");
                    if (yn == true)
                    {
                        char file[20];
                        if (input_string(file, 20, "Input name of the file with table: ") == IO_ERR)
                            printf("Invalid file name, can not open the table.\n");
                        else
                        {
                            printf("your file is - %s\n", file);
                            if (save_table(file, flats, length) == OK)
                                printf("Saved.\n");
                        }
                    }
                }
            }
            flats = create(&length);
            if (flats == NULL)
                printf("Can not create a table.\n");
            else
            {
                printf("The database is created.\n");
                printf("LINE\n");
                print_line(*flats[1]);
            }
        }
        else if (action == ACTION_4)//add an el
        {
            printf("action 4\n");
            ft** tmp = realloc(flats, (length + 1) * sizeof(ft*));
            if (tmp)
            {
                ft* data = NULL;
                data = malloc((length + 1) * sizeof(ft));
                if (data)
                {
                    flats = tmp;
                    flats[length] = &data[length];
                    if (add_line(data, length) == OK)
                    {
                        printf("Added\n");
                        length ++;
                    }
                    else
                    {
                        printf("can not add a line\n");
                        ft** tmp = realloc(flats, length * sizeof(ft*));
                        if (tmp)
                        {
                            ft* tmp2 = malloc(length * sizeof(ft));
                            if (tmp2)
                            {
                                data = tmp2;
                                flats = tmp;
                            }
                        }
                    }
                }
                else
                    printf("Can not add a line\n");
            }
            else printf("Can not add a line\n");
        }
        else if (action == ACTION_5)//save
        {
            char file[20];
            if (input_string(file, 20, "Input name of the file with table: ") == IO_ERR)
                printf("Invalid file name, can not open the table.\n");
            else
            {
                printf("your file is - %s\n", file);
                if (save_table(file, flats, length) == OK)
                    printf("Saved.\n");
            }
        }
        else if (action == ACTION_6)//delete
        {
            delete(flats, &length);
            print_table(flats, length);
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
