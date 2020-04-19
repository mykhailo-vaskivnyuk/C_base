/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Заняття 3. Процедури і функції.
 * Частина 7. Передавання параметрів функції за посиланням.
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 19.05.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.0.0 Основан на Qt 5.2.0 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/* ЗАВДАННЯ
Напишіть програму, яка виконує наступне:
1) приймає з клавіатури два цілих числа;
2) передає їх за посиланням у функцію Mul();
3) функція Mul() інкрементує отримані аргументи (змінні з іншими іменами!) і перемножує їх;
4) результат функції Mul() передається в основну програму з виведенням на екран у вигляді виразу (наприклад, з клавіатури прийнято a=7 i b=3; на екрані повинно з'явитися 8*4=32).
*/

#include <stdio.h>

void iptIntNumbers(int *a, int *b); //function for entering integer numbers
int Mul(int *c, int *d); //function for result

int main(void)
{
    int a = 0, b = 0;

    iptIntNumbers(&a, &b);
    printf("YOU ENTERED NUMBERS %d AND %d\n\n", a, b);
    printf("THE RESULT IS: %d * %d = %d\n", a, b, Mul(&a, &b));
    getch();
    return 0;
}

int Mul(int *c, int *d)
{
    return ++*c * ++*d;
}

void iptIntNumbers(int *a, int *b)
{
    int count_numbers = 0;
    int int_tmp = 0;

    while(count_numbers++ < 2)
    {
        while(1)
        {
            printf("ENTER %d NUMBER: ", count_numbers);
            _flushall();
            int_tmp = 0;
            scanf("%d", &int_tmp);
            printf("\n");
            if(int_tmp != 0) break;
            printf("WRONG NUMBER! TRY AGAIN!\n");
         }

        (count_numbers == 1) ? (*a = int_tmp) : (*b = int_tmp);
    }
}
