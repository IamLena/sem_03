#include"derectives.h"
#include "input.h"
#include "output.h"

void search(void)
{
    int flag = 0;
    char key[20];
    char* keys[3] = {"id", "adress", "rooms"};
    if (input_string(key, 20, "Input key for search: ") == OK)
    {
        printf("%s\n", key);
        for (int i = 0; i < 3; i ++)
        {
            if (strcmp(key, keys[i]) == 0)
            {
                flag = 1;
                printf("okay\n");
                break;
            }
        }
        if (flag == 1)
        {

        }


    }
    printf("Invalid input\n");

}
int main(void)
{
    ft* flats_ptr[5];
    ft flats_data[5];
    for (int i = 0; i < 5; i ++)
        flats_ptr[i] = &flats_data[i];
    print_table(flats_ptr, 5);
    search();
    return 0;
}
