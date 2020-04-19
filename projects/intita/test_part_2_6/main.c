/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Заняття 2. Основи мови С. Частина 1.
 * Частина 6. Оператори введення-виведення.
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 16.05.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.0.0 Основан на Qt 5.2.0 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/* ЗАВДАННЯ
Напишіть цикл (будь-якого типу) для введення чисел у наведеному зразку програми.
Кожне число має вводитись на окремій ітерації циклу.
Для вибору необхідної змінної використайте оператор switch().
*/

#include <stdio.h>

int main(void)
{
    int cntr = 0; //counter
    int number = 0;
    int first = 0, second = 0, third = 0;

    printf("ENTER 3 NUMBERS!\n");

    for(cntr = 1; cntr <= 3; cntr++)
    {
        printf("ENTER %d NUMBER: \n", cntr);
        _flushall();
        number = 0;
        scanf("%d", &number);

        switch(cntr)
        {
            case 1:
                first = number;
                break;
            case 2:
                second = number;
                break;
            case 3:
                third = number;
                break;
        }
    }

    printf("YOUR NUMBERS ARE\n");
    printf("-first:  %5d\n", first);
    printf("-second: %5d\n", second);
    printf("-third:  %5d\n", third);

    getchar();

    return 0;
}
