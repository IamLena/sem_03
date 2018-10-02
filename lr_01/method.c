#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<time.h>

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );
    return d;
}

void random_array(int*pb, int *pe)
{
    int r;
    for (int *i = pb; i < pe; i++)
    {
        r = 0 + rand() % 10;
        *(i) = r;
    }
    *(pe - 1) = 0;
}

int print( const int *ab, const int *ae)
{
    assert((ab != NULL) && (ae != NULL) && (ab < ae));
    for (const int *run = ab; run < ae; run++)
        printf("%d ", *run);
    printf("\n");
    return 0;
}
void sum1(int *a, int *b, int n)
{
    int r = 0;
    int s[n];
    for (int i = 0; i < n; i ++)
    {
        s[i] = (a[i] + b[i]) % 10 + r;
        r = (a[i] + b[i]) / 10;
        if (s[i] == 10)
        {
            s[i] = 0;
            r ++;
        }
    }
    print(s, s + n);
}

void sum2(int *a, int *b, int n)
{
    int *s = NULL;
    int i = 0;
    int r = 0;
    int length = 1 * sizeof(int);
    while (i < n)
    {
        int *tmp = realloc(s, length);
        if(tmp)
            s = tmp;
        else
            return;
        *(s + i) = (*(a + i) + *(b + i)) % 10 + r;
        r = (*(a + i) + *(b + i)) / 10;
        if (*(s + i) == 10)
        {
            *(s + i) = 0;
            r ++;
        }

        length += sizeof(int);
        i ++;
    }
    print(s, s + n);
}


int main(void)
{
    srand(time(NULL));
    unsigned long long t1, t2, t;
    int a[30];
    int b[30];
    random_array(a, a + 30);
    random_array(b, b + 30);
    print(a, a + 30);
    print(b, b + 30);
    t1 = tick();
    sum1(a, b, 30);
    t = tick();
    t1 = t - t1;
    printf("sum1 - %lu\n", (unsigned long)t1);
    t2 = tick();
    sum2(a, b, 30);
    t = tick();
    t2 = t - t2;
    printf("sum2 - %lu\n", (unsigned long)t2);
    unsigned long t_dif = (unsigned long)t2 - (unsigned long)t1;
    printf("dif: %lu\n", t_dif);
    t_dif /= 2400000000;//2.40Ггц - тактовая частота процессора
    printf("dif: %lu sec\n", t_dif);
    return 0;
}
