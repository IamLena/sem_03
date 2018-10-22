#include "derectives.h"
#include "input.h"
#include "add.h"
#include "output.h"
#include "delete.h"
#include "sort.h"
#include "file.h"

void menu(void)
{
    printf("MENU\n");
    printf("1) Print table\n");
    printf("2) Open a database\n");
    printf("3) Create a new database\n");
    printf("4) Add an element\n");
    printf("5) Delete an element\n");
    printf("6) Search\n");
    printf("7) Sort with keys\n");
    printf("8) Sort the table without keys\n");
    printf("9) Info about efficiency\n");
    printf("10) Save the table\n");
    printf("11) Info about author\n");
    printf("12) Exit\n");
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
        printf("action - %d\n", action);
        if (action == ACTION_1)//print
        {
            if (print_table(flats, length) == IO_ERR)
                printf("There is no data.\n");
        }
        else if (action == ACTION_2)//open
        {
            if (flats != NULL)
            {
                printf("OPENING TABLE\n");
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
                            printf("Invalid file name, can not save the table.\n");
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
            printf("CREATING THE TABLE\n");
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
                            printf("Invalid file name, can not save the table.\n");
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
                printf("The database is created.\n");
        }
        else if (action == ACTION_4)//add an el
        {
            printf("ADDING A LINE\n");
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
        else if (action == ACTION_5)//delete
        {
            printf("DELETING AN ELEMENT\n");
            if (delete(flats, &length) == OK)
            {
                printf("here\n");
                ft **tmp1 = realloc(flats, length * sizeof(ft*));
                ft *tmp2 = realloc(flats[0], length * sizeof(ft));
                if (tmp1 && tmp2)
                {
                    printf("reallocating\n");
                    flats = tmp1;
                    for (int i = 0; i < length; i ++)
                        flats[i] = &tmp2[i];
                }
            }
            print_line(*flats[length]);
            print_table(flats, length);
        }
        else if (action == ACTION_6)//search
        {
            printf("FILTER\n");
            if (search(flats, length) == IO_ERR)
                printf("Can not find such elements.\n");
        }
        else if (action == ACTION_7)//sort with keys
        {
            printf("SORTING WITH KEYS\n");
            sort(flats, length);

        }
        else if (action == ACTION_8)//sort without keys
        {
            printf("SORTING WITHOUT KEYS\n");
           sort_flats(flats, length);
        }
        else if (action == 9)
        {
            printf("EFFICIENCY\n");
        }
        else if (action == ACTION_10)//save
        {
            printf("SAVING THE TABLE\n");
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
        else if (action == 11)
        {
            printf("INFO\n");
            printf("IU7-31b\nLuchina Lena\nlab_02\n");
        }
        else if (action == 12)
        {
            printf("exit\n");
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
                            printf("Invalid file name, can not save the table.\n");
                        else
                        {
                            printf("your file is - %s\n", file);
                            if (save_table(file, flats, length) == OK)
                                printf("Saved.\n");
                        }
                    }
                }
            }
        }
        else
            printf("Invalid input\n");
        rc = IO_ERR;
        while (rc != OK)
            rc = input_bool(&yn, "Do you want to continue work? ");
    }
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
        if (flats[0] != NULL)
            free (flats[0]);
        free(flats);
    }
    return OK;
}
