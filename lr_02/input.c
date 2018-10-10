#include "derectives.h"

void clean_stdin(void)
{
    //printf("clearing! ");
    char c = 'a';
    while (c != '\n' && c != EOF)
    {
        c = getchar();
        //printf("%c", c);
    }
    //printf("\n");
}

int input_bool(bool *value, char *key)
{
    printf("%s ", key);
    printf("y/n: ");
    bool tmp;
    char c;
    int rc = OK;
    c = getchar();
    if (c != EOF && c != '\n')
    {
        if (c == 'y' || c == 'Y')
            tmp =  true;
        else if (c == 'n' || c == 'N')
            tmp = false;
        else
            rc = IO_ERR;

        if (((c = getchar()) == '\n'))
        {
            if (rc == OK)
                *value = tmp;
        }
        else
        {
            clean_stdin();
            rc =  IO_ERR;
        }
    }
    else
        rc = IO_ERR;
    return rc;
}

int input_action(void)
{
    int act;
    char c;
    printf("chose an action (input the number): ");
    c = getchar();
    if (c != EOF && c != '\n')
    {
        if (isdigit(c))
        {
            if (c == '1')
                act = ACTION_1;
            else if (c == '2')
                act = ACTION_2;
            else if (c == '3')
                act = ACTION_3;
            else if (c == '4')
                act = ACTION_4;
            else if (c == '5')
                act = ACTION_5;
            else if (c == '6')
                act = ACTION_6;
            else
                act = IO_ERR;
        }
        else
            act = IO_ERR;
        if (((c = getchar()) != '\n'))
        {
            clean_stdin();
            act =  IO_ERR;
        }
    }
    else
        act = IO_ERR;
    return act;
}

int input_string(char *str, int n, char *key)
{
    //printf("Adress (<50 symbols): ");
    printf("%s", key);
    char c;
    int rc = OK;
    int i = 0, flag = 0;
    bool yn;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        if (i < n - 1)
            str[i++] = c;
        else
            flag = 1;
    }
    str[i] = '\0';
    if (flag == 1 || i == 0)
    {
        printf("Empty input or reached the maximum size of holder\n");
        rc = IO_ERR;
        while (rc != OK)
            rc = input_bool(&yn, "Want to try again? ");
        if (yn == true)
            rc = input_string(str, n, key);
        if (yn == false)
            rc = IO_ERR;
    }
    return rc;
}

int input_float(float *size, char *key)
{
    printf("%s", key);
    int rc = OK;
    float tmp;
    bool yn;
    if (scanf("%f", &tmp) != 1)
    {
        clean_stdin();
        printf("Invalid input\n");
        rc = IO_ERR;
        while (rc != OK)
            rc = input_bool(&yn, "Want to try again? ");
        if (yn == true)
            rc = input_float(size, key);
        if (yn == false)
            rc = IO_ERR;
    }
    else
    {
        if (tmp <= 0)
        {
            printf("<=0\n");
            clean_stdin();
            printf("Invalid input\n");
            rc = IO_ERR;
            while (rc != OK)
                rc = input_bool(&yn, "Want to try again? ");
            if (yn == true)
                rc = input_float(size, key);
            if (yn == false)
                rc = IO_ERR;
        }
        else
        {
            *size = tmp;
            clean_stdin();
        }
    }
    return rc;
}

int input_si(short int *a, char *key)
{
    bool yn;
    printf("%s", key);
    int rc = OK;
    short int tmp;
    if (scanf("%hi", &tmp) != 1)
    {
        clean_stdin();
        printf("Invalid input\n");
        rc = IO_ERR;
        while (rc != OK)
            rc = input_bool(&yn, "Want to try again? ");
        if (yn == true)
            rc = input_si(a, key);
        if (yn == false)
            rc = IO_ERR;
    }
    else
    {
        if(!(0 < tmp && tmp <= 32767))
        {
            printf("<=0\n");
            clean_stdin();
            printf("Invalid input\n");
            rc = IO_ERR;
            while (rc != OK)
                rc = input_bool(&yn, "Want to try again? ");
            if (yn == true)
                rc = input_si(a, key);
            if (yn == false)
                rc = IO_ERR;
        }
        else
        {
            *a = tmp;
            clean_stdin();
        }
    }
    return rc;
}

int input_int(int* a, char *key)
{
    bool yn;
    printf("%s", key);
    int rc = OK;
    int tmp;
    if (scanf("%d", &tmp) != 1)
    {
        clean_stdin();
        printf("Invalid input\n");
        rc = IO_ERR;
        while (rc != OK)
            rc = input_bool(&yn, "Want to try again? ");
        if (yn == true)
            rc = input_int(a, key);
        if (yn == false)
            rc = IO_ERR;
    }
    else
    {
        if (tmp < 0 || tmp > 4294967295)
        {
            clean_stdin();
            printf("Invalid input\n");
            rc = IO_ERR;
            while (rc != OK)
                rc = input_bool(&yn, "Want to try again? ");
            if (yn == true)
                rc = input_int(a, key);
            if (yn == false)
                rc = IO_ERR;
        }
        else
        {
            *a = tmp;
            clean_stdin();
        }
    }
    return rc;
}

int add_line(ft*flats, int length)
{
    int rc;
    printf("adding line\n");
    struct flat_t new;

    new.id = length;
    rc = input_string(new.adress, ADRESS_LEN, "Adress (<50 symbols): ");
    if (rc != OK)
        return IO_ERR;
    rc = input_float(&new.size, "Size (m^2): ");
    if (rc != OK)
        return rc;
    rc = input_si(&new.rooms, "How many rooms does it have? ");
    if (rc != OK)
        return rc;
    rc = input_int(&new.price, "What is the price of 1 sq.m? ");
    if (rc != OK)
        return rc;
    rc = input_bool(&new.is_new, "Is the flat new? ");
    if (rc == IO_ERR)
        return rc;
    if (new.is_new)
    {
        printf("new flat\n");
        rc = input_bool(&new.type.newflat.finished, "Is it repaired? ");
        if (rc == IO_ERR)
            return rc;
    }
    else
    {
        rc = input_si(&new.type.oldflat.year, "When was it built? ");
        if (rc != OK)
            return rc;
        rc = input_si(&new.type.oldflat.owners, "How many people have owned it? ");
        if (rc != OK)
            return rc;
        rc = input_si(&new.type.oldflat.dwellers, "How many people lived here before? ");
        if (rc != OK)
            return rc;
        rc = input_bool(&new.type.oldflat.animal, "Were there any animals? ");
        if (rc == IO_ERR)
            return rc;
    }
    printf("%hu %s %f %hu %hd ", new.id, new.adress, new.size, new.rooms, new.price);
    if (new.is_new == true)
    {
        printf("new ");
        if (new.type.newflat.finished == true)
            printf("finished ");
        else
            printf("not finished");
    }
    else
    {
        printf("old %hu %hu %hu ", new.type.oldflat.year, new.type.oldflat.owners, new.type.oldflat.dwellers);
        if (new.type.oldflat.animal == true)
            printf("with animals");
        else
            printf("without animals");
    }
    bool yn;
    rc = IO_ERR;
    while (rc != OK)
        rc = input_bool(&yn, "\nIs this element correct? Do you want to add it? ");
    if (yn == true)
    {
        *(flats + length) = new;
        printf("Added\n");
    }
    else
    {
        printf("The line isn't added.\n");
        rc = IO_ERR;
    }


    return rc;
}

//int main(void)
//{
//    ft *flats[10];
//    add_line(flats, 0);
//}
