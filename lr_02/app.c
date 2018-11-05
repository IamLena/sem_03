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
    ft *flats = NULL;
    int length = 0;
    bool yn = true;
    int saved_flag = 0;
    int rc;

    while (yn)
    {
        menu();
        int action = input_action();
        if (action == ACTION_1)//print
        {
            printf("PRINTING THE TABLE\n");
            if (print_table(flats, length) == IO_ERR)
                printf("There is no data.\n");
        }
        else if (action == ACTION_2)//open
        {
            if (flats != NULL)
            {
                if (saved_flag == 0)
                {
                    printf("OPENING THE TABLE\n");
                    printf("Your existing table can be deleted.\nMake sure you have saved it.\n");
                    bool yn;
                    int code = 1;
                    while (code != OK)
                    {
                        code = input_bool(&yn, "Do you want to save it now? ");
                        if (yn == true)
                        {
                            char file[20];
                            if (input_string(file, 20, "Input name of the file (where to save): ") == IO_ERR)
                                printf("Invalid file name, can not save the table.\n");
                            else
                                if (save_table(file, flats, length) == OK)
                                {
                                    saved_flag = 1;
                                    printf("Saved in %s.\n", file);
                                }
                        }
                    }
                }
                else
                    printf("Be aware you have a opened saved table\n");
            }
            printf("OPENING THE TABLE\n");
            char file[20];
            if (input_string(file, 20, "Input name of the file (with the table): ") == IO_ERR)
                printf("Invalid file name, can not open the table.\n");
            else
                if (read_table(file, &flats, &length) == OK)
                {
                    printf("Opened, you can proceed to work.\n");
                    saved_flag = 1;
                }
        }
        else if (action == ACTION_3)//create
        {
            if (flats != NULL)
            {
                printf("CREATING A NEW TABLE\n");
                if (saved_flag == 0)
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
                            if (input_string(file, 20, "Input name of the file (where to save): ") == IO_ERR)
                                printf("Invalid file name, can not save the table.\n");
                            else
                                if (save_table(file, flats, length) == OK)
                                {
                                    saved_flag = 1;
                                    printf("Saved in %s.\n", file);
                                }
                        }
                    }
                }
                else
                    printf("Be aware you have a opened saved table\n");
            }
            printf("CREATING A NEW TABLE\n");
            flats = create(&length);
            if (flats == NULL)
                printf("Can not create a table.\n");
            else
            {
                printf("The database is created.\n");
                saved_flag = 0;
            }
        }
        else if (action == ACTION_4)//add an el
        {
            printf("ADDING AN ELEMENT\n");
            ft *tmp = realloc(flats, (length + 1) * sizeof(ft*));
            if (tmp)
            {
                if (add_line(tmp, length) == OK)
                {
                    saved_flag = 0;
                    length ++;
                    flats = tmp;
                }
                else
                {
                    printf("1 can not add a line\n");
                    free(tmp);
                }
            }
            else
                printf("3 can not add a line.\n");
        }
        else if (action == ACTION_5)//delete
        {
            printf("DELETING AN ELEMENT\n");
            delete(&flats, &length);
        }
        else if (action == ACTION_6)//search
        {
            printf("FILTER\n");
            //поиск всего вторичного 2-х комнатного жилья в указанном ценовом диапазоне без животных.
            printf("2 rooms flat without animals in the specified price range\n");
            if (search(flats, length) == IO_ERR)
                printf("Can not find such elements.\n");
        }
        else if (action == ACTION_7)//sort with keys
        {
            printf("SORTING WITH KEYS\n");
            k_el *table = sort_keys(flats, length);
            if (table)
            {
                print_keys(table, length);
                print_head();
                for (int i = 0; i < length; i ++)
                {
                    printf("%3d", i);
                    int struct_index = table[i].index;
                    print_line(flats[struct_index]);
                }
                free(table);
            }
        }
        else if (action == ACTION_8)//sort without keys
        {
            printf("SORTING WITHOUT KEYS\n");
            ft *sorted = sort_flats(flats, length);
            if (sorted)
            {
                print_table(sorted, length);
                free(sorted);
            }
        }
        else if (action == 9)
        {
            printf("INFO ABOUT EFFICIENCY\n");
            if (flats == NULL)
                printf("open or create a table first\n");
            else
            {
                printf("\t....\nCALCULATING EFFICIENCY\n");
                unsigned long t1, t2;
                t1 =  tick();
                k_el *table1 = sort_keys(flats, length);
                t2 = tick();
                if (table1)
                {
                    free(table1);
                }
                unsigned long t_sort1 = t2 - t1;
                t1 =  tick();
                k_el *table2 = sort_keys_shaker(flats, length);
                t2 = tick();
                if (table2)
                {
                    free(table2);
                }
                unsigned long t_sort2 = t2 - t1;
                t1 =  tick();
                ft *sorted1 = sort_flats(flats, length);
                t2 = tick();
                if(sorted1)
                {
                    free(sorted1);
                }
                unsigned long t_sort3 = t2 - t1;
                t1 =  tick();
                ft *sorted2 = sort_flats_shaker(flats, length);
                t2 = tick();
                if(sorted2)
                {
                    free(sorted2);
                }
                unsigned long t_sort4 = t2 - t1;
                printf("Bubble sort keys = %lu\n", t_sort1);
                printf("Shaker sort keys = %lu\n", t_sort2);
                printf("Bubble sort the table (pointers) = %lu\n", t_sort3);
                printf("Shaker sort the table (pointers) = %lu\n", t_sort4);
            }
        }
        else if (action == ACTION_10)//save
        {
            printf("SAVING THE TABLE\n");
            char file[20];
            if (input_string(file, 20, "Input name of the file (where to save): ") == IO_ERR)
                printf("Invalid file name, can not open the table.\n");
            else
                if (save_table(file, flats, length) == OK)
                {
                    saved_flag = 1;
                    printf("Saved in %s.\n", file);
                }
        }
        else if (action == 11)
        {
            printf("MADE BY\n");
            printf("Luchina Lena IU7-31b\nlab_02\n");
        }
        else if (action == 12)
        {
            printf("EXIT\n");
        }
        else
            printf("Invalid input\n");
        rc = IO_ERR;
        while (rc != OK)
            rc = input_bool(&yn, "Do you want to continue work? ");
    }
    if (flats != NULL && saved_flag == 0)
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
        free(flats);
    }
    printf("exiting the program");
    return OK;
}
