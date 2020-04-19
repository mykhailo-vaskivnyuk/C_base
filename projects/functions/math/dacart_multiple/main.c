/*
Задача 1. Напишіть програму, яка виконує декартів добуток двох множин
(одновимірних масивів цілих чисел). Результат (новоутворена множина)
повинна бути збережена в двовимірний масив.
--------------------------------------------------------------------------------
Задача 2. Дано дві множини чисел: A={1,5,17,18,45};  B={2,10,34,12,9,45,90}.
Напишіть програму, яка формує з цих множин відношення "дільник".
Елементи вказаного відношення - пари чисел (a, b), де a - дільник числа b.
--------------------------------------------------------------------------------
Задача 3. Дано дві множини:
A={"Great Britain","Canada","Argentina"};
B={"Football","Hockey","Field hockey","Track and field","Tennis"};
Необхідно створити відношення "В країні розвинутий такий вид спорту",
яке б формувалося за допомогою таблиці (двовимірного масиву) розмірністю NxM,
де N - розмірність (потужність) множини А (кількість країн), М -
потужність множини В (кількість видів спорту)
Рядки і стовпці таблиці закріплені за країнами і видами спорту (чи навпаки).
На перетині рядка і стопця, які відповідають країні і розвинутому в ній видові
спорту, має стояти 1, решта комірок заповнюються 0 (масив вводиться з клавіатури).
Програма повинна в кінці вивести на екран відношення у вигляді сукупності фраз:
"В країні ... розвинутий вид спорту ..." (на основі даних з таблиці відношення).
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>

#define TEST_2

int funcTest_1(void);
int funcTest_2(void);

int  multArray      (int *, int, int *, int, int *, bool (*)(int, int));
void setArrayInt    (int *, int);
void printArrayInt  (int *, int);
void printArrayInt_2(int *, int, int,   int);

bool ifDiv(int, int);

int main(void)
{
    puts("\0");
    while( 1 )
    {
#if   defined TEST_1
        funcTest_1();
#elif defined TEST_2
        funcTest_2();
#elif defined TEST_3
        funcTest_3();
#endif
        puts("\0");
        puts("TO TRY AGAIN PRESS ANY KEY. TO EXIT - PRESS 'q'.\n");
        if( 'q' == getch() ) break;
    }

    return 0;
}

int funcTest_1(void)
{
    int N = 3;
    int M = 4;

    int * array_1 = (int*)malloc(N * sizeof(int));
    int * array_2 = (int*)malloc(M * sizeof(int));
    int (* array)[2] = (int (*)[2])malloc(N * M * 2 * sizeof(int));

    setArrayInt(array_1, N);
    setArrayInt(array_2, M);

    system("cls");
    puts("\0");
    printArrayInt(array_1, N);
    puts("\0");
    printArrayInt(array_2, M);
    multArray(array_1, N, array_2, M, (int *)array, NULL);
    puts("\0");
    printArrayInt_2((int *)array, N * M, 2, 0);
    return 0;
}

int funcTest_2(void)
{
    int N = 5;
    int M = 7;
    int count = 0;

    //int * array_1 = (int*)malloc(N * sizeof(int));
    //int * array_2 = (int*)malloc(M * sizeof(int));
    int array_1[5] = {1,  5, 17, 18, 45};
    int array_2[7] = {2, 10, 34, 12,  9, 45, 90};
    int (* array)[2] = (int (*)[2])malloc(N * M * 2 * sizeof(int));

    //setArrayInt(array_1, N);
    //setArrayInt(array_2, M);

    system("cls");
    puts("\0");
    printArrayInt(array_1, N);
    puts("\0");
    printArrayInt(array_2, M);
    count = multArray(array_1, N, array_2, M, (int *)array, ifDiv);
    puts("\0");
    printArrayInt_2((int *)array, count, 2, 0);
    return 0;
}

int multArray(int * array_1, int array_size_1, int * array_2, int array_size_2, int * array_result, bool (*condition)(int, int))
{
    int * ptr_array_2 = array_2;
    int   count       = 0;

    do
    {
        do
        {
            if( condition == NULL || condition(*array_1, *array_2) )
            {
                *array_result = *array_1;
                array_result++;
                *array_result = *array_2;
                array_result++;
                count++;
            }
            array_2++;
        }while(--array_size_2);

        array_size_2 = array_2 - ptr_array_2;
        array_2 = ptr_array_2;
        array_1++;

    }while(--array_size_1);

    return count;
}

void printArrayInt(int * array, int array_size)
{
    int i = 0;

    puts("\0");

    for(i = 0; i < array_size; i++)
        printf("%4d ", i + 1);
    puts("\0");
    puts("\0");

    for(i = 0; i < array_size; i++)
        printf("%4d ", *(array + i));

    puts("\0");
}

void setArrayInt(int * array, int array_size)
{
    while( array_size-- )
        *(array + array_size) = (rand() % 100);
}

void printArrayInt_2(int * array, int array_size_N, int array_size_M, int type)
{
    int i     = 0;
    int j     = 0;
    int index = 0;

    puts("\0");

    for(i = 0; i < array_size_M; i++)
        printf("%4d ", i + 1);
    puts("\0");
    puts("\0");

    for(i = 0; i < array_size_N; i++)
    {
        for(j = 0; j < array_size_M; j++)
        {
            index = type ? (j * array_size_N + i) : (i * array_size_M + j);
            printf("%4d ", *(array + index));
        }
        puts("\0");
    }
    puts("\0");
}

bool ifDiv(int a, int b)
{
    return b % a == 0;
}
