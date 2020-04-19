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

#include <stdio.h>
#include <string.h>
#include <strings.h> //здається стара
#include <windows.h> //не стандартна
#include <conio.h> //не стандартна
#include <stdbool.h> //не стандартна
#include <locale.h>
#include <io.h> //не стандартна
//fcntl.h
//sys\stat.h
#include <stdlib.h> // для застосування функції system
//#include <unistd.h> //не стандартна
  //sleep()
//#include <pthread.h>
#pragma pack(push, 1)
#pragma pack(pop)
//#pragma C99 ON
//#define func_3() func_3(100)

int func(void);
int func_3(int);

int main(void)
{
    #define N 34;
/*
    system("chcp 1251"); // переходим в консоли на русский язык
    system("cls");

    printf("ПРИВІТ");
    return 0;
*/
    func_3(100);
    Sleep(500);
    printf("\n%s\n", "hello");
    //system("cls");
    return 0;

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
int func_3(int number)
{
    char a;
    unsigned char b;

    //a = 200;
    b = number + 200;
    //b = a;
    a = b;
    printf("%d %d", a, b);
    return 0;
}

int func_2(void)
{
    int i = 0;
    int a = 0;
    a = (1 == 1 ? (i = 3) : (i = 5));
    printf("%d %d\n", i, a);
    return 0;
}

int func(void)
{
    int i = 0;
    int j = 0;
    int k = 0;

    j = scanf("%d%d", &i, &k);
    printf("%d\n\n", j);

    for( ; i < k; i++)
    {
        printf("%d\n", i);
    }

    printf("\n%d\n", i);

    return 1;
}
