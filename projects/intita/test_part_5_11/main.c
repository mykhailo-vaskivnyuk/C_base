/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Заняття 5. Символьні рядки.
 * Частина 11. Об'єднання рядків.
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 23.05.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.0.0 Основан на Qt 5.2.0 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/* ЗАВДАННЯ
Напишіть програму, яка в циклі do-while виконує наступні дії:
   - вводяться рядки s1 і s2 ;
   - здійснюється перевірка, чи достатньо місця для їх об'єднання має той рядок, який буде приймачем;
   - якщо достатньо - здійснюється об'єднання рядків і результат (рядок-приймач) виводиться на екран;
   - якщо недостатньо - цикл повторюється.
*/

#include <stdio.h>
#include <string.h>
#define MAX_STR_LEN 50

void delEnter(char * string); //delete '\n' from string

int main(void)
{
    char s1[MAX_STR_LEN + 1] = "";
    char s2[MAX_STR_LEN + 1] = "";
    int i = 0;

    do
    {
        if(s1[0] != '\0' || s2[0] != '\0') //for second iteration
        {
            printf("\n");
            printf("LENGTH STRING_1 + LENGTH STRING_2 IS %d SYMBOLS.\n", strlen(s1) + strlen(s2));
            printf("IT IS MORE THAN %d.\n", MAX_STR_LEN);
            printf("PRESS ANY KEY TO TRY AGAIN.\n");
            printf("\n");
        }

        printf("INPUT TWO STRINGS.\n");
        printf("LENGTH STRING_1 + LENGTH STRING_2 HAS NOT TO BE MORE THAN %d SYMBOLS.\n", MAX_STR_LEN);
        printf("\n");

        i = 0;
        while( i++ < 2 )
        {
            printf("THE %d STRING: ", i);
            fflush(stdin);
            switch(i)
            {
                case 1:
                    fgets(s1, MAX_STR_LEN + 1, stdin);
                    delEnter(s1);
                    break;
                case 2:
                    fgets(s2, MAX_STR_LEN + 1, stdin);
                    delEnter(s2);
                    break;
            }
        }
    }
    while(strlen(s1) + strlen(s2) > MAX_STR_LEN);

    strcat(s1, s2);
    printf("\n");
    printf("THE RESULT STRING IS: %s\n", s1);

    printf("\n");
    printf("press any key to exit\n");

    return 0;
}

void delEnter(char * string)
{
    do
    {
        if(*string == '\n')
            *string = '\0';
    }
    while(*string++ != '\0');
}
