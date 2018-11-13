#include "derectives.h"
#include "input.h"
#include "output.h"

/**
 * @brief delete удаляет запись из таблицы по номеру
 * @param flats начало массива структур
 * @param length длина таблицы
 * @return код возврата
 *
 * Если длина таблицы равна нулю или указатель нулевой - сообщаем пользователю, что таблицу пустая и выходим из функции.
 * Иначе выводим таблицу наэкран и спрашиваем у пользователя, элемент под каким носером он хочет удалить.
 * Считываем этот номер и проверяем, что такой в таблице есть. Если нет - возвращаем ошибкую
 * Полученный номер минус 1 (индеусация с нуля) - это индекс данного лемента в массиве.
 * Двигаем память, освобождаем последний элемент и уменьшаем значение длины.
 */
int delete(ft **flats, int *length)
{
    if (flats == NULL || *flats == NULL || *length == 0)
    {
        printf("nothing to delete. The table is empty\n");
        return DEL_ERR;
    }
    int index;
    int rc = OK;
    print_table(*flats, *length);
    input_int(&index, 3, "Input the number of the element you want to delete: ");
    printf("the value is %d\n", index);
    if (index <= 0 || index > *length)
    {
        printf("Haven't found\n");
        rc = DEL_ERR;
    }
    else
    {
        printf("this line \n");
        print_line((*flats)[index - 1]);
        if (index < *length)
        {
            printf("replace with this\n");
            print_line((*flats)[index]);
            printf("moving %d\n", (int)(*length - index));
            printf("moving %d\n", (int)((*length - index)*sizeof(ft)));
            memmove(*flats + index - 1, *flats + index, (*length - index) * sizeof(ft));
        }
        *length -= 1;
        printf("table in del\n");
        ft *tmp = realloc(*flats, *length * sizeof(ft));
        if (tmp)
            *flats = tmp;
        print_table(*flats, *length);
    }
    return rc;
}

/**
 * @brief search - Фильтрует таблицу
 * Найти все вторичное 2-х комнатное жилье в указанном ценовом диапазоне без животных
 * @param flats начало массива
 * @param length длина массива
 * @return код ошибки
 * Программа запрашивает минимальную и максимальную цены диапазона
 * проверяет корректность ввода.
 * Потом идет в цикле по элементам массива и сравнивает элемент со значением определенным фильтром.
 * Если программа находит такой элемент и он первый найденный, выводится шапка таблицы.
 * Далее выводится этот элемент массива.
 * Если по завершении цикла счетчик все еще равен нулю - значит таких элементов не нашлось,
 * сообщим об этом ползователю и вернем соответсвующий код ошибки.
 */
int search(ft *flats, int length)//sorting price with keys
//Найти все вторичное 2-х комнатное жилье в указанном ценовом диапазоне без животных
{
    int lp, rp;
    if (input_int(&lp, 9, "Input the lowest price: (0, 999999999)") == IO_ERR)
        return IO_ERR;
    if (input_int(&rp, 9, "Input the highest price: (0,999999999)") == IO_ERR)
        return IO_ERR;
    int count = 0;
    for (int i = 0; i < length; i ++)
    {
        if (flats[i].rooms == 2 && flats[i].type.oldflat.animal == false && flats[i].is_new == false && flats[i].price > lp && flats[i].price < rp)
        {
            if (count == 0)
                print_head();
            printf("%3d", count + 1);
            print_line(flats[i]);
            count++;
        }
    }
    if (count == 0)
    {
        printf("There are no such elements\n");
        return EMPTY_ERR;
    }
    return OK;
}
