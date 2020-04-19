/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Заняття 5. Символьні рядки.
 * Частина 14. Підсумкове завдання.
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 25.05.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.2.1 Основан на Qt 5.3.2 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/* ЗАВДАННЯ
Напишіть програму, що реалізує наступні дії:
1) введення з клавіатури даних:
   - два рядки str1 і str2 (з можливістю запису пробілів у відповідні змінні);
   - цілі числа n1 i n2 (значення яких не перевищують довжину відповідних рядків);
2) створити дві процедури, які б здійснювали:
   - отримання в якості параметрів введених вище змінних;
   - створення нового рядка, який би складався з n1 перших символів рядка
str1 (на початку) і n2 останніх символів рядка str2 (в кінці).
   - виведення на екран новоутвореного рядка.
3) кожна процедура повинна формувати новий рядок по-різному:
   - шляхом копіювання одночасно цілої групи символів з рядків str1 і str2;
   - шляхом посимвольного копіювання необхідних літер з відповідних рядків;
4) доступ до введених рядків (чи їх окремих символів) повинен здійснюватися
за допомогою покажчиків на рядок.
*/

#include <stdio.h>
#include <string.h>
#define MAX_STRING_LEN 80

void firstTask(char *, char *, int, int);
void secondTask(char *, char *, int, int);
void inputNumber(int *, int, int);

int main(void)
{
    char stg_1[MAX_STRING_LEN + 1] = "";
    char stg_2[MAX_STRING_LEN + 1] = "";
    int stg_pos_1 = 0;
    int stg_pos_2 = 0;
    char * ptr_stg_1 = stg_1;
    char * ptr_stg_2 = stg_2;

    puts("INPUT TWO STRINGS.");
    //first string
    puts("THE FIRST:");
    gets(ptr_stg_1);
    //second string
    puts("THE SECOND:");
    gets(ptr_stg_2);

    inputNumber(&stg_pos_1, 1, strlen(ptr_stg_1));
    inputNumber(&stg_pos_2, 1, strlen(ptr_stg_2));

    firstTask(ptr_stg_1, ptr_stg_2, stg_pos_1, stg_pos_2);
    secondTask(ptr_stg_1, ptr_stg_2, stg_pos_1, stg_pos_2);

    return 0;
}

void firstTask(char * stg_1, char * stg_2, int stg_pos_1, int stg_pos_2)
{
    char stg[MAX_STRING_LEN * 2 + 1] = "";

    //copy to result initial stg_pos_1 symbols from stg_1
    strncpy(stg, stg_1, stg_pos_1);

    //add to result stg_pos_2 last symbols from stg_2
    stg_2 += strlen(stg_2) - stg_pos_2;
    strcat(stg, stg_2);

    puts("THE FIRST RESULT IS:");
    puts(stg);
}

void secondTask(char * stg_1, char * stg_2, int stg_pos_1, int stg_pos_2)
{
    char stg[MAX_STRING_LEN * 2 + 1] = "";
    char * ptr_stg = stg;

    //copy to result initial stg_pos_1 symbols from stg_1
    while(stg_pos_1--)
        *ptr_stg++ = *stg_1++;

    //copy to result stg_pos_2 last symbols from stg_2
    stg_2 += strlen(stg_2) - stg_pos_2;
    while( (*ptr_stg++ = *stg_2++) );

    puts("THE SECOND RESULT IS:");
    puts(stg);
}

void inputNumber(int * number, int min_limit, int max_limit)
{
    while(1)
    {
        printf("INPUT INT NUMBER FROM %d TO %d: \n", min_limit, max_limit);
        fflush(stdin);
        *number = 0;
        scanf("%d", number);
        if( *number >= min_limit && *number <= max_limit) break;
        printf("NUMBER %d IS WRONG!\n", *number);
    }
}

/*  printf("sizeof(stg_1) : %d\n", sizeof(stg_1));
    printf("sizeof stg_1 : %d\n", sizeof stg_1);
    printf("sizeof(stg_1[0]) : %d\n", sizeof(stg_1[0]));
    printf("sizeof stg_1[0] : %d\n", sizeof stg_1[0]);
    printf("sizeof(&stg_1[0]) : %d\n", sizeof(&stg_1[0]));
    printf("sizeof &stg_1[0] : %d\n", sizeof &stg_1[0]);
    printf("sizeof(&stg_1) : %d\n", sizeof(&stg_1));
    printf("sizeof &stg_1 : %d\n", sizeof &stg_1);
    return 0;
*/
