#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#include "types.h"
#include "output.c"

#define OK 0
#define IO_ERR 101

#define NEW 11
#define OLD 22

void clean_stdin(void)
{
    char c = 'a';
    while (c != '\n' && c != EOF)
        c = getchar();
}

int input_adress(char *str, int n)
{
    printf("Adress (<50 symbols): ");
    char c;
    int rc = OK;
    int i = 0, flag = 0;
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
        printf("Want to try again? y/n \n");
        if(((c = getchar()) != EOF) && (c == 'y' || c == 'Y') && ((c = getchar()) == '\n'))
            rc = input_adress(str, n);
        else
            rc =  IO_ERR;
    }
    return rc;
}

int input_size(float *size)
{
    printf("Size (m^2): ");
    int rc = OK;
    float tmp;
    if (scanf("%f", &tmp) != 1)
    {
        printf("Invalid input\n");
        printf("Want to try again? y/n \n");
        char c;
        clean_stdin();
        if(((c = getchar()) != EOF) && (c == 'y' || c == 'Y') && ((c = getchar()) == '\n'))
            rc = input_size(size);
        else
            rc = IO_ERR;
    }
    else
        *size = tmp;
    clean_stdin();
    return rc;
}

int input_usi(unsigned short int* a, char *key)
{
    printf("%s", key);
    int rc = OK;
    unsigned short int tmp;
    if (scanf("%hu", &tmp) != 1)
    {
        printf("Invalid input\n");
        printf("Want to try again? y/n \n");
        char c;
        clean_stdin();
        if(((c = getchar()) != EOF) && (c == 'y' || c == 'Y') && ((c = getchar()) == '\n'))
            rc = input_usi(a, key);
        else
            rc = IO_ERR;
    }
    else
        *a = tmp;
    clean_stdin();
    return rc;
}

int input_ui(unsigned int* a, char *key)
{
    printf("%s", key);
    int rc = OK;
    unsigned short int tmp;
    if (scanf("%hd", &tmp) != 1)
    {
        printf("Invalid input\n");
        printf("Want to try again? y/n \n");
        char c;
        clean_stdin();
        if(((c = getchar()) != EOF) && (c == 'y' || c == 'Y') && ((c = getchar()) == '\n'))
            rc = input_ui(a, key);
        else
            rc = IO_ERR;
    }
    else
        *a = tmp;
    clean_stdin();
    return rc;
}

int input_bool(bool *value, char *key)
{
    printf("%s ", key);
    printf("y/n: ");
    bool tmp;
    char c;
    c = getchar();
    if (c != EOF && c != '\n')
    {
        if (c == 'y' || c == 'Y')
            tmp =  true;
        else if (c == 'n' || c == 'N')
            tmp = false;
        else
            return IO_ERR;
        if ((c = getchar()) == '\n')
        {
            *value = tmp;
            return tmp;
        }
        else
            return IO_ERR;
    }
    else
        return IO_ERR;
}

bool eq_str(char *s1, char *s2)
{
    if (strlen(s1) != strlen(s2))
        return false;
    for (int i = 0; s1[i] != '\0'; i++)
        if (s1[i] != s2[i])
            return false;
    return false;

}

int det_type()
{
    char answer[4];
    int i = 0, flag = 0;
    char c;
    int rc;
    printf("Is this flat old or new? (old/new): ");
    while ((c = getchar()) != '\n' && c != EOF)
    {
        if (i < 3)
            answer[i++] = c;
        else
            flag = 1;
    }
    answer[i] = '\0';
    if (flag == 1)
    {
        printf("Empty input or reached the maximum size of holder\n");
        printf("Want to try again? y/n \n");
        if(((c = getchar()) != EOF) && (c == 'y' || c == 'Y') && ((c = getchar()) == '\n'))
            rc = det_type();
        else
            rc =  IO_ERR;
    }
    if (eq_str(answer, "new"))
        rc = NEW;
    else if (eq_str(answer, "old"))
        rc = OLD;
    else
        rc = IO_ERR;

    return rc;
}

int read(const char* filename_dst, struct flat_t**flats, int lastline)
{
    int rc;
    printf("adding line\n");
    struct flat_t new;

    new.id = lastline + 1;
    rc = input_adress(new.adress, ADRESS_LEN);
    if (rc != OK)
        return IO_ERR;
    rc = input_size(&new.size);
    if (rc != OK)
        return rc;
    rc = input_usi(&new.rooms, "How many rooms does it have? ");
    if (rc != OK)
        return rc;
    rc = input_ui(&new.price, "What is the price of 1 sq.m? ");
    if (rc != OK)
        return rc;
    rc = input_bool(&new.is_new, "Is the flat new? ");
    printf("rc - %d", rc);
    if (rc == IO_ERR)
        return rc;
    if (rc == 1)
    {
        printf("new flat\n");
        rc = input_bool(&new.type.newflat.finished, "Is it repaired? ");
        if (rc == IO_ERR)
            return rc;
    }
    else
    {
        rc = input_usi(&new.type.oldflat.year, "When was it built? ");
        if (rc != OK)
            return rc;
        rc = input_usi(&new.type.oldflat.owners, "How many people have owned it? ");
        if (rc != OK)
            return rc;
        rc = input_usi(&new.type.oldflat.dwellers, "How many people lived here before? ");
        if (rc != OK)
                return rc;
        rc = input_bool(&new.type.oldflat.animal, "Were there any animals? ");
        if (rc == IO_ERR)
            return rc;
    }

//    struct flat_t**tmp = realloc(flats, (lastline + 1) * sizeof(struct flat_t*));
//    if (!tmp)
//    {
//        printf("Can not add a line, memory error\n");
//        return MEM_ERR;
//    }
//    flats = tmp;
//    FILE *f = fopen(filename_dst, "w");
    printf("done\n");
    print_line(new);
    return OK;
}
