/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Заняття 5. Символьні рядки.
 * Частина 7. Операції над рядками: визначення довжини.
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 22.05.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.0.0 Основан на Qt 5.2.0 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/* ЗАВДАННЯ
Реалізуйте в програмному коді наступні можливості:
1) ввести з клавіатури число, яке дорівнює граничній довжині рядка;
2) в циклі do-while виконайте:
   - введення з клавіатури рядка;
   - визначення довжини рядка і виведення результату на екран;
   - повторення циклу за умови, якщо довжина рядка менша граничної.
*/

#include <stdio.h>
#include <string.h>

int main(void)
{
    int max_str_length = 0;
    int cur_str_length = 0;
    char * p_str;
    int i = 0;

    while(1) //input max string length
    {
        printf("\n");
        printf("INPUT MAX STRING LENGHT: ");
        fflush(stdin);
        max_str_length = 0;
        scanf("%d", &max_str_length);
        printf("\n");
        printf("YOU'VE INPUT THE NUMBER: %d\n", max_str_length);

        if(max_str_length > 0)
            break;

        printf("IT IS WRONG NUMBER!\n");
        printf("PRESS ANY KEY TO TRY ONE MORE TIME!\n");
        getch();
    }

    char string[max_str_length + 1];
    string[0] = '\0';

    while(1) //input string
    {
        printf("\n");
        printf("INPUT A %d SYMBOL STRING: ", max_str_length);
        fflush(stdin);
        gets(p_str);
        printf("\n");
        printf("YOU'VE INPUT THE STRING: %s:\n", p_str);
        printf("THE STRING LENGTH IS: %d\n", cur_str_length = strlen(p_str));

        if(cur_str_length == max_str_length)
        {
            printf("IT IS RIGHT!\n");
            break;
        }
        printf("\n");
        printf("PRESS ANY KEY TO TRY ONE MORE TIME!\n");
        getch();
    }

    strncat(string, p_str, max_str_length); //fill the string array
    while(string[i++] = *p_str++);

    printf("to exit press any key\n");
    getch();
    return 0;
}
