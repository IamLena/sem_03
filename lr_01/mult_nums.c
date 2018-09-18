#include <stdio.h>
#include <string.h>
#include<ctype.h>
#include<assert.h>

#define OK 0
#define OVER 1
#define IO_ERR 2

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
    assert(s != NULL);
    int n;
    char c;
    printf("Input the number.\n");
    printf("+/-|                              |\n   ");
    fgets(s, 32, stdin);
    n = strlen(s);
    if(!(*s == '+' || *s == '-' || (isdigit(*s) && n < 32)))
        return IO_ERR;

    for (int i=1; i<n-1; i++)
    {
        if (!(isdigit(*(s+i))))
            return IO_ERR;
    }
    if(n == 32 || (isdigit(*s) && n == 31))
        if (scanf("%c", &c) == 1)
            return IO_ERR;
    return OK;
}

void make_array(char* s, int* a, int n)
{
    assert((s!= NULL)&&(a!=NULL));
    //int n = strlen(s)-1;
    assert(n > 0);
    for (int i = 0; i < n; i++)
        *(a+i) = *(s + i) - '0';
}

void print_array(int*beg, int*end)
{
    assert((beg!=NULL) && (end!= NULL));
    printf("[ ");
    for(int* i = beg; i<end; i++)
        printf("%d ",*i);
    printf("]\n");
}

//int sum(int*a, int n, int*b, int m, int *sum, int d)
//{
//    int mem = 0;
//    int r = (n > m ? n : m);

//}

int main(void)
{
    char buf[32];
    int rc;

    rc = input_int(buf);
    if(rc == IO_ERR)
        //printf("invalid input");
    printf("%s\n", buf);
    int n = strlen(buf)-1;
    int s1[n];
    if(*buf == '+')
    {
        s1[0] = 1; //for positive
        make_array(buf+1, s1+1, n);
    }
    if (isdigit(*buf))
    {
        s1[0] = 1;
        n++;
        make_array(buf, s1+1, n);
    }
    if (*buf == '-')
    {
        s1[0] = 0; //for negative
        make_array(buf+1, s1+1, n);
    }
    print_array(s1, s1+n);

    printf("%d", r);
    return rc;
}
