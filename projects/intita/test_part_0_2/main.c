/*
1. Оголосити покажчик на масив типу double. З клавіатури - ввести розмірність масиву.
   Подальші дії - реалізувати в циклі і за допомогою наступних чотирьох функцій:
    а) динамічне виділення пам'яті під масив;
    б) заповнення масиву даними (з клавіатури чи випадково);
    в) виведення даних масиву на екран;
    г) звільнення виділеної під масив пам'яті.
   В кінці циклу користувач повинен щось ввести з клавіатури або щось натиснути, щоб:
    1) повторити все спочатку;
    2) завершити роботу програми.

2. Оголосити покажчик на масив типу int. З клавіатури - ввести розмірність масиву (не менше 12).
   Після заповнення масиву даними - реалізуйте функцію, яка:
    - оцінює розмірність масиву (введене число) на парність/непарність;
    - якщо кількість ел-тів парна - переставляє в зворотньому порядку лише парні елементи масиву,
      в протилежному випадку - відповідно непарні.
      При цьому елементи, які не переставляються, залишаються в своїх комірках.
   Вивести змінений масив на екран для контролю.

3. Оголосити покажчик на покажчик типу int.
   За його допомогою - створити динамічний двовимірний масив
   (кількість рядків і стовпчиків попередньо ввести з клавіатури). За допомогою окремих функцій:
    - заповнити масив випадковими числами від 10 до 50;
    - вивести на екран у вигляді ТРАНСПОНОВАНОЇ матриці.
   Кожна функція має вхідні параметри: покажчик на масив, кількість рядків, кількість стовпців.
*/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TEST_2
#define ARRAY_MAX_SIZE 20

void funcTest_1     (void);
void funcTest_2     (void);
void funcTest_3     (void);

bool iniArray       (double **, int);
void setArray       (double *,  int);
void printArray     (double *,  int);
void freeArray      (double **);

void printArrayInt  (int *,     int);
bool ifPair         (int);
bool ifNotPair      (int);

void setArrayInt_2  (int *,     int, int);
void printArrayInt_2(int *,     int, int, int);

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

void funcTest_1(void)
{
    double * ptr_array       = NULL;
    int      array_size      = 0;

//------------------------------------------------------------------------------
//  вводимо (з клавіатури) розмірність масиву
//------------------------------------------------------------------------------

    while( 1 )
    {
        printf("INPUT ARRAY SIZE (1 TO %d): ", ARRAY_MAX_SIZE);
        fflush(stdin);
        array_size = 0;
        scanf("%d", &array_size);
        if( array_size > 0 && array_size <= ARRAY_MAX_SIZE) break;
        puts("\0");
        puts("WRON ARRAY SIZE. TRY AGAIN!");
    }

//------------------------------------------------------------------------------
//  виділяємо пам'ять під масив
//------------------------------------------------------------------------------

    if( !iniArray(&ptr_array, array_size) )
    {
        //неможливо виділити память під масив
        return;
    }

//------------------------------------------------------------------------------
//  заповнюємо масив
//------------------------------------------------------------------------------

    setArray(ptr_array, array_size);

//------------------------------------------------------------------------------
//  виводимо масив на екран
//------------------------------------------------------------------------------

    printArray(ptr_array, array_size);

//------------------------------------------------------------------------------
//  звільняємо память
//------------------------------------------------------------------------------

   freeArray(&ptr_array);
}

bool iniArray(double ** array, int array_size)
{
    *array = (double *)malloc(array_size * sizeof(double));
    return ( *array != NULL );
}


void setArray(double * array, int array_size)
{
    while( array_size-- )
        *(array + array_size) = (rand() % 1000) / 10;
}


void printArray(double * array, int array_size)
{
    int i = 0;

    system("cls");
    puts("\0");

    for(i = 0; i < array_size; i++)
        printf("%4d   ", i + 1);
    puts("\0");
    puts("\0");

    for(i = 0; i < array_size; i++)
        printf("%6.2f ", *(array + i));

    puts("\0");
}

void freeArray(double ** array)
{
    free(array);
    *array = NULL;
}

void funcTest_2(void)
{
    int   * ptr_array       = NULL;
    int   * ptr_arr_1       = NULL;
    int   * ptr_arr_2       = NULL;
    int     array_size      = 0;
    int     i               = 0;
    int     j               = 0;
    int     tmp             = 0;
    bool (* condition)(int) = NULL;

//------------------------------------------------------------------------------
//  вводимо (з клавіатури) розмірність масиву
//------------------------------------------------------------------------------

    while( 1 )
    {
        printf("INPUT ARRAY SIZE (1 TO %d): ", ARRAY_MAX_SIZE);
        fflush(stdin);
        array_size = 0;
        scanf("%d", &array_size);
        if( array_size > 0 && array_size <= ARRAY_MAX_SIZE) break;
        puts("\0");
        puts("WRON ARRAY SIZE. TRY AGAIN!");
    }

//------------------------------------------------------------------------------
//  виділяємо пам'ять під масив
//------------------------------------------------------------------------------

    ptr_array = (int *)malloc(array_size * sizeof(int));
    if( ptr_array == NULL )
    {
       //неможливо виділити память під масив
       return;
    }

//------------------------------------------------------------------------------
//  заповнюємо масив
//------------------------------------------------------------------------------

    for(i = 0; i < array_size; i++ )
        *(ptr_array + i) = rand() % 100;

//------------------------------------------------------------------------------
//  виводимо масив на екран
//------------------------------------------------------------------------------

    system("cls");
    printArrayInt(ptr_array, array_size);

//------------------------------------------------------------------------------
//  переставляємо елементи ВАРІАНТ 1
//------------------------------------------------------------------------------

    condition = (array_size & 1) ? ifNotPair : ifPair;

    j = array_size - 1;
    for(i = 0; i < j; i++)
    {
        if( !condition(*(ptr_array + i)) ) continue;
        for( ; j > i ; j--)
        {
            if( !condition(*(ptr_array + j)) ) continue;
            tmp = *(ptr_array + i);
            *(ptr_array + i) = *(ptr_array + j);
            *(ptr_array + j) = tmp;

            j--;
            break;
        }
    }

//------------------------------------------------------------------------------
//  виводимо масив на екран
//------------------------------------------------------------------------------

        puts("\0");
        printArrayInt(ptr_array, array_size);

//------------------------------------------------------------------------------
//  переставляємо елементи ВАРІАНТ 2
//------------------------------------------------------------------------------

    ptr_arr_1 = ptr_array;
    ptr_arr_2 = ptr_array + array_size - 1;
    do
    {
        if( !condition(*ptr_arr_1) ) continue;
        do
        {
            if( !condition(*ptr_arr_2) )continue;
            tmp = *ptr_arr_1;
            *ptr_arr_1 = *ptr_arr_2;
            *ptr_arr_2 = tmp;

            ptr_arr_2--;
            break;
        }while( ptr_arr_1 < --ptr_arr_2 );
    }while( ++ptr_arr_1 < ptr_arr_2 );

//------------------------------------------------------------------------------
//  виводимо масив на екран
//------------------------------------------------------------------------------

    puts("\0");
    printArrayInt(ptr_array, array_size);

//------------------------------------------------------------------------------
//  звільняємо память
//------------------------------------------------------------------------------

   free(ptr_array);

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

bool ifPair (int number)
{
    return !(number % 2);
}

bool ifNotPair (int number)
{
    return number & 1;
}

void funcTest_3()
{
    int     array_size_N    = 0;
    int     array_size_M    = 0;

//------------------------------------------------------------------------------
//  вводимо (з клавіатури) розмірність масиву
//------------------------------------------------------------------------------

    while( 1 )
    {
        printf("INPUT ARRAY SIZE N (1 TO %d): ", ARRAY_MAX_SIZE);
        fflush(stdin);
        array_size_N = 0;
        scanf("%d", &array_size_N);
        if( array_size_N > 0 && array_size_N <= ARRAY_MAX_SIZE) break;
        puts("\0");
        puts("WRON ARRAY SIZE N. TRY AGAIN!");
    }

    while( 1 )
    {
        printf("INPUT ARRAY SIZE M (1 TO %d): ", ARRAY_MAX_SIZE);
        fflush(stdin);
        array_size_M = 0;
        scanf("%d", &array_size_M);
        if( array_size_M > 0 && array_size_M <= ARRAY_MAX_SIZE) break;
        puts("\0");
        puts("WRON ARRAY SIZE M. TRY AGAIN!");
    }

//------------------------------------------------------------------------------
//  виділяємо пам'ять під масив
//------------------------------------------------------------------------------
    int (*ptr_array_2)[array_size_M] = NULL;
    ptr_array_2 = (int (*)[array_size_M])malloc(array_size_N * array_size_M * sizeof(int));
    if( ptr_array_2 == NULL )
    {
       //неможливо виділити память під масив
       return;
    }

//------------------------------------------------------------------------------
//  заповнюємо масив
//------------------------------------------------------------------------------

    setArrayInt_2((int *)ptr_array_2, array_size_N, array_size_M);

//------------------------------------------------------------------------------
//  виводимо масив на екран
//------------------------------------------------------------------------------

    system("cls");
    printArrayInt_2((int *)ptr_array_2, array_size_N, array_size_M, 0);
    puts("\0");
    printArrayInt_2((int *)ptr_array_2, array_size_M, array_size_N, 1);

}

void setArrayInt_2(int * array, int array_size_N, int array_size_M)
{
    int array_size = array_size_N * array_size_M;
    while( array_size-- )
    {
        do
        {
            *(array + array_size) = rand() % 51;
        }while( *(array + array_size) < 10);
    }
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
