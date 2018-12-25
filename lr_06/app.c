#include <stdio.h>
#include <stdlib.h>

int is_simple(int num)
{
    for (int i = 2; i * i <= num; i++)
        if (num % i == 0)
            return 0;
    return 1;
}

int generate_simple(int num)
{
    if (num <= 0)
        return 0;
    for (int i = 1;; i++)
    {
        if (i >= num)
        {
            if (is_simple(i))
                return i;
        }
    }
}

int count(FILE *f)
{
    int count = 0;
    int num;
    while (fscanf(f, "%d", &num) == 1)
    {
        count++;
    }
    return count;
}

void print_arr(int *arr, int n)
{
    if (arr == NULL || n <= 0)
        return;
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int read_file(FILE *f, int **arr, int *arr_len)
{
    int num;

    int length = count(f);
    rewind(f);

    if (length == 0)
    {
        printf("Invalid content\n");
        return -1;
    }
    int *tmp_arr = malloc(length * sizeof(int));
    if (!tmp_arr)
        return -2;

    for (int i = 0; i < length; i++)
    {
        fscanf(f, "%d", &num);
        tmp_arr[i] = num;
    }

    *arr_len = length;
    *arr = tmp_arr;
    return 0;
}

int hash(int num, int length)
{
    return (num % length);
}

struct node
{
    int value;
    struct node *next;
};

void print_hash(struct node **hash_table, int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%d->", i);
        struct node *cur = hash_table[i];
        while(cur != NULL)
        {
            printf("%d->", cur->value);
            cur = cur->next;
        }
        printf("\n");
    }
}

int make_hashtable(int *numbers, int length, struct node ***table, int *hash_length)
{
    int index;
    int depth = 0;
    int hash_len = generate_simple(length);
    struct node **hash_table = malloc(hash_len * sizeof(struct node*));
    if (!hash_table)
        return -2;
    for (int i = 0; i < hash_len; i++)
        hash_table[i] = NULL;
    for (int i = 0; i < length; i++)
    {
        index = hash(numbers[i], hash_len);
        struct node* cur = hash_table[index];
        if (cur == NULL)
        {
            printf("dep = %d\n", depth);
            struct node *element = malloc(sizeof(struct node));
            if (!element)
            {
                printf("mem\n");
                return -1;
            }
            else
            {
                element->value = numbers[i];
                element->next = NULL;
            }
            hash_table[index] = element;
        }
        else
        {
        while(cur->next != NULL)
        {
            //depth++;
            cur = cur->next;
        }
        printf("dep = %d\n", depth);
            struct node *element = malloc(sizeof(struct node));
            if (!element)
            {
                printf("mem\n");
                return -1;
            }
            else
            {
                element->value = numbers[i];
                element->next = NULL;
            }
            cur->next = element;
        }
    }
    *table = hash_table;
    *hash_length = hash_len;
    return 0;
}

int find(int num, struct node **table, int length)
{
    int count = 0;
    int index = hash(num, length);
    while (table[index]->value != num)
    {
        if (table[index]->next != NULL)
        {
            struct node *cur = table[index];

            count++;

        }
        else
            return 0;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("app.exe in.txt");
        return -1;
    }
    FILE *f = fopen(argv[1], "r");
    if (!f)
    {
        printf("cannot open file\n");
        return -1;
    }
    int *array;
    int len;
    read_file(f, &array, &len);
    print_arr(array, len);

    struct node **table;
    int hash_len;

    make_hashtable(array, len, &table, &hash_len);
    print_hash(table, hash_len);
    return 0;
}
