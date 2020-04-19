/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Заняття 5. Символьні рядки.
 * Частина 8. Порівняння рядків.
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 22.05.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.0.0 Основан на Qt 5.2.0 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/* ЗАВДАННЯ
В наведений приклад внесіть наступну модифікацію - запрограмуйте цикл do-while , в якому:
а) з клавіатури вводиться ціле число n;
б) в заданих рядках за допомогою функції strncmp(str1, str2, n) порівнюються n перших символів;
в) результат порівняння частин рядків ("співпадають" чи "не співпадають") виводиться на екран;
г) якщо результат порівняння не дорівнює 0 - цикл повторюється.
{
char str1[] = "Australia"; // ініціалізуємо
char str2[] = "Austria"; // два рядки
if ( 0 == strcmp(str1,str2) ) // якщо рядки однакові -
printf("String %s is identical to %s", str1, str2); // констатуємо це
else printf("String %s is not identical to %s", str1, str2); // інакше - заперечуємо
}
*/

#include <stdio.h>
#include <string.h>

int function_from_ITA(int symbols_count);
int iptSymbolsCount(void);

int main(void)
{
    while(1)
    {
        if( function_from_ITA(iptSymbolsCount()) )
            break;

        printf("\n");
        printf("PRESS ANY KEY TO TRY ONE MORE TIME!\n");
        getch();
    }

    printf("\n");
    printf("to exit press any key\n");
    getch();
    return 0;
}

int function_from_ITA(int symbols_count)
{
    char str1[] = "Australia"; // ініціалізуємо
    char str2[] = "Austria"; // два рядки

    if ( 0 == strncmp(str1, str2, symbols_count) ) // якщо рядки однакові -
    {
        printf("The %d symbols of string %s is identical to %s\n", symbols_count, str1, str2); // констатуємо це
        return 1;
    }

    printf("The %d symbols of String %s is not identical to %s\n", symbols_count, str1, str2); // інакше - заперечуємо
    return 0;
}

int iptSymbolsCount(void)
{
    int symbols_count = 0;

    while(1) //input symbols count
    {
        printf("\n");
        printf("INPUT SYMBOLS COUNT: ");
        fflush(stdin);
        symbols_count = 0;
        scanf("%d", &symbols_count);
        printf("\n");
        printf("YOU'VE INPUT THE NUMBER: %d\n", symbols_count);

        if(symbols_count > 0)
            break;

        printf("IT IS WRONG NUMBER!\n");
        printf("PRESS ANY KEY TO TRY ONE MORE TIME!\n");
        getch();
    }

    return symbols_count;
}
