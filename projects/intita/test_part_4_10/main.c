/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Заняття 4. Покажчики та рекурсія.
 * Частина 10. Що таке рекурсія.
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 20.05.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.0.0 Основан на Qt 5.2.0 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/* ЗАВДАННЯ
Реалізуйте програмно рекурсивну функцію Natural(), яка будує ряд
натуральних чисел (з виведенням на екран):
1) початкове значення ряду: x(1) = 1;
2) кожне наступне значення: x(n+1) = x(n)+1 ;
3) умова завершення - досягнення певного граничного значення N.
*/

#include <stdio.h>

void prtNatural(unsigned short); //VARIANT 1
//void prtNatural(unsigned short int *); //VARIANT 2

int main(void)
{
    short int number = 0;
    while(1)
    {
        printf("\n");
        printf("ENTER NUMBER FROM 1 TO 100: ");
        _flushall();
        number = 0;
        scanf("%d", &number);
        printf("\n");

        if( number <= 0 || number > 100 )
        {
            printf("WRONG NUMBER! TRY AGAING!\n");
            continue;
        }

        prtNatural(number);

        if( getch() == 'q') break;
    }
    return 0;
}

void prtNatural(unsigned short number)
{
    if(number > 1)
        prtNatural(number - 1);

    printf("%3d\n", number);
}

/*
void prtNatural(unsigned short int *number)
{
    if(*number > 1)
    {
        --*number;
        prtNatural(number);
    }

    printf("%3d\n", (*number)++);
}
*/
