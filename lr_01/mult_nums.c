#include <stdio.h>
#include <string.h>
#include<ctype.h>

#define OK 0
#define OVER 1
#define NOT_NUM 2

int input_float(char*s)
{
    char c;
    int n;
    printf("Input the number.\n");
    printf("|                              |\n ");
    fgets(s, 31, stdin);
    n = strlen(s);
    for (int i=0; i<n; i++)



    if(n < 30 && scanf("%c", &c) == 1)
        return OVER;



    printf("%s\n", s);
//    printf("%c\n", *(s+2));
    printf("%d\n", strlen(s));
    return OK;
}

int input_int(char*s)
{
    int n;
    char c;
    printf("Input the number.\n");
    printf("|                              |\n ");
    fgets(s, 31, stdin);
    n = strlen(s);
    for (int i=0; i<n; i++)
    {
        if (!(isdigit(*(s+i))))
        {
            printf("not a number");
                return NOT_NUM;
        }
    }
    if(n == 30)
        if (scanf("%c", &c) == 1)
        {
            printf("over");
            return OVER;
        }

    printf("%s\n", s);
    printf("%d\n", strlen(s));
    return OK;
}

int main(void)
{
    char s1[31];
    //char s2[31];
    int rc;

    rc = input_int(s1);
//    if (rc == OK)
//    {
//        rc = input_int(s2);
//        if(rc == OK)
//            return rc;
//    }
//    printf("invalid num");
    return rc;
}
