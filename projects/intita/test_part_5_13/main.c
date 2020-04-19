/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Заняття 5. Символьні рядки.
 * Частина 13. Форматування рядків та читання з них.
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 24.05.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.2.1 Основан на Qt 5.3.2 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/* ЗАВДАННЯ
Реалізуйте програмно наступні дії:
1) з клавіатури вводяться 2 дійсні числа (у відповідні змінні);
2) за допомогою функції sprintf() введені числа записуються (через пробіл)
у рядок str у цілочисельному форматі;
3) результат (рядок str) вивести на екран;
4) провести зворотне перетворення - функцією sscanf() прочитати з рядка str числа;
5) записати прочитані числа у дійсному форматі у вже існуючі (або нові) змінні (використовуючи формат %g), результат - на екран;
6) якщо матиме місце різниця між початковими і кінцевими значеннями змінних - спробувати пояснити причину.
*/

#include <stdio.h>
#include <conio.h>

#define MAX_STRING 80

int main(void)
{
    float a = 0;
    float b = 0;
    char string[80 + 1] = "";

    while(1)
    {
        puts("-----------------------------------------");
        puts("input two float numbers (input format g):");
        a = 0; b = 0;
        fflush(stdin);
        scanf("%g%g", &a, &b);
        printf("\n");

        printf("you've input (output format 10g):    %10g %10g\n", a, b);
        printf("you've input (output format 10.2f):  %10.2f %10.2f\n", a, b);

        sprintf(string, "%10d %10d", (int) a, (int) b);
        puts("sprintf(str, \"format\", a, b) -> puts(str):");
        printf("you've input (output format 10d): ");
        puts(string);

        a = 0; b = 0;
        sscanf(string, "%g%g", &a, &b);
        puts("sscanf(str, \"format\", &a, &b) -> printf(\"format\", a, b):");
        printf("you've input (output in 10g format):    %10g %10g\n", a, b);

        printf("\n");
        puts("press any key to try again or \'q\' for exit");
        if( getch() == 'q' ) break;
    }

    return 0;
}
