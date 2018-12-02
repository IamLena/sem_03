#include <stdio.h>
#include <stdbool.h>
#include<assert.h>

/// переворачивает число
/// \param[in] a число
/// \return перевернутое число или код ошибки
int reverse (int a)
{
    assert(a >= 0);
    int m = 0;
    int d;

    while (a > 0)
    {
        d = a % 10;
        a = a / 10;
        m = m * 10 + d;
     }
    return m;
}

/// узнает, является ли число палиндромом
/// \param[in] a число
/// \return истина (1) - если число являет палиндромом, иначе ложь (0)

bool palindrom (int a)
{
    if (a < 0)
        return false;
    if (a == reverse(a))
        return true;
    else
        return false;
}
