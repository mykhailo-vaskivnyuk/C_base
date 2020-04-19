/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Заняття 4. Покажчики та рекурсія.
 * Частина 14. Підсумкове завдання.
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 21.05.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.0.0 Основан на Qt 5.2.0 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/* ЗАВДАННЯ
Складіть програму для виконання наступних дій:
1) оголошується покажчик int* sum; (для роботи з динамічним масивом);
2) створюється рекурсивна функція побудови ряду натуральних чисел до певного
граничного значення їх суми;
3) створюється динамічний масив розмірністю N (кількість натуральних чисел в побудованому ряді);
4) масив заповнюється величинами: sum[i]=(i+1)+sum[i-1]; де (i+1) -
чергове натуральне число, sum[i-1] - сума попередніх чисел натурального ряду.
*/

#include <stdio.h>
#define SUM_LIMIT 20 //more than 0

void getMaxNumber(int sum_limit, int * number);

int main(void)
{
    int number = 0; //max number of natural row
    int i = 0; //counter
    int * arr_sum = NULL; //pointer on result array sum[i] = (i+1) + sum[i-1]

    printf("SUM_LIMIT: %d\n", SUM_LIMIT);
    getMaxNumber(SUM_LIMIT, &number);
    printf("NATURAL NUMBER: %d\n", number);

    int array[number]; //dynamic result array
    arr_sum = array;

    arr_sum[0] = (1 + 1) + 0; //for first number of natural row: 1
    for(i = 1; i < number; i++) //for second and others numbers of natural row: 2, 3, ...
        arr_sum[i] = ((i + 1) + 1) + arr_sum[i - 1];

    for(i = 0; i < number; i++)//printing
        printf("%2d :: %3d\n", i + 1, arr_sum[i]);

    return 0;
}

void getMaxNumber(int sum_limit, int * number)
{
    if( (sum_limit -= *number + 1) < 0)
        return;
    ++*number;
    getMaxNumber(sum_limit, number);
}
