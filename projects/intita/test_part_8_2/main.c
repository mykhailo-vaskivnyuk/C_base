/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Заняття 8. Типи даних, визначені користувачем (частина 1).
 * Частина 2. Тип користувача “перерахування”: стандартний спосіб оголошення.
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 03.06.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.2.1 Основан на Qt 5.3.2 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/* ЗАВДАННЯ
1. Запрограмуй аналогічні перерахування BOOLEAN і функцію,
   яка приймає параметр типу BOOLEAN.
2. Перевір результат роботи програми, передавши у функцію
   замість синонімів їх чисельні еквіваленти (відповідно 0 і 1).
*/

#include <stdio.h>

enum BOOLEAN
{
    FALSE
   ,TRUE
};

void printEnum_1(enum BOOLEAN);
void printEnum_2(int);

int main(void)
{
    enum BOOLEAN bl;
    int bl_int;

    bl = FALSE;
    printEnum_1(bl);
    printEnum_1(FALSE);
    printEnum_1(0);

    bl = TRUE;
    printEnum_1(bl);
    printEnum_1(TRUE);
    printEnum_1(1);

    bl = 0;
    bl = 1;
    bl = 2; //bl можна використовувати як змінну int
    printf("%d\n", bl);
    printEnum_1(bl);
    printEnum_2(bl);

    bl_int = bl;
    printEnum_1(bl_int); //змінну типу int можна передавати під параметр типу enum
    printEnum_2(bl_int);

    return 0;
}

void printEnum_1(enum BOOLEAN bl)
{
    printf("VALUE %d: \n", bl);
}

void printEnum_2(int bl)
{
    printf("VALUE %d: \n", bl);
}
