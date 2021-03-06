/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Заняття 4. Покажчики та рекурсія.
 * Частина 9. Особливості масивів великих розмірів.
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 20.05.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.0.0 Основан на Qt 5.2.0 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/* ЗАВДАННЯ
Напишіть функцію, яка б мала вхідним параметром статичний масив arr з
20 дійсних чисел і виконувала наступне:
1) підрахунок (із записом відповідної кільності у змінну N) від’ємних чисел у масиві arr;
2) створити 2 динамічні масиви (розмірністю N і 20-N),
в які окремо розмістити від’ємні і додатні числа з масиву arr;
3) порахувати середнє арифметичне обох масивів;
4) в динамічному масиві, середнє арифметичне елементів якого виявиться більше (за модулем) -
записати це середнє арифметичне замість елемента (елементів), який (які) виявиться до нього найближчим(и);
5) змінений в п.4. динамічний масив скопіювати до масиву arr (в перші N або 20-N комірок),
решту комірок масиву arr - обнулити;
6) повернути через return масив arr.
*/

#include <stdio.h>
#include <math.h>

float * f(float array[]);

int main(void)
{
    int cr = 0;
    float array[20] = {1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12, 13, -14, 15, -16, 17, -18, -19, -20};
    float *arr = array;

    arr = f(array);
    for(cr = 0; cr < 20; cr++)
        printf("%f\n", arr[cr]);

    return 0;
}

float * f(float array[])
{
    int N = 0;
    int i = 0, j = 0, k = 0;

    for(i = 0; i < 20; i++)
    {
        if(array[i] < 0)
            N++;
    }

    float arr_1[N];
    float arr_2[20 - N];
    float average_1 = 0;
    float average_2 = 0;
    float max_av = 0;
    float *pt = NULL;
    float mindif = 0;

    for(i = 0; i < 20; i++)
    {
        if(array[i] < 0)
        {
            arr_1[j++] = array[i];
            average_1 += array[i];
        }
        else
        {
            arr_2[k++] = array[i];
            average_2 += array[i];
        }
    }

    average_1 /= N;
    average_2 /= 20 - N;

    if(-average_1 >= average_2)
    {
        pt = arr_1;
        max_av = average_1;
    }
    else
    {
        pt = arr_2;
        N = 20 - N;
        max_av = average_2;
    }

    mindif = fabs(max_av);
    for(i = 0; i < N; i++)
    {
        if(mindif > fabs(max_av - pt[i]))
            mindif = fabs(max_av - pt[i]);
    }

    for(i = 0; i < N; i++)
    {
        if(mindif == fabs(max_av - pt[i]))
            pt[i] = max_av;
    }

    for(i = 0; i < 20; i++)
    {
        array[i] = (i < N) ? pt[i] : 0;
    }

    return array;
}
