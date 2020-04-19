/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Заняття 6. Текстові файли.
 * Частина 7. Текстові файли: введення-виведення даних.
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 26.05.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.2.1 Основан на Qt 5.3.2 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/* ЗАВДАННЯ
Реалізуй програму для виконання наступних дій:
1) послідовне читання з файлу input.txt одночасно трьох чисел;
2) запис їх у файл output.txt в рядок і в послідовності: 2-е, 1-е, 3-є.
*/

#include <stdio.h>


int main(void)
{
    FILE * inFile = NULL;
    FILE * outFile = NULL;
    int numbers[3] = {};
    int i = 0;

    //inFile = fopen("input.txt", "w");
    //fclose(inFile);
    //return 0;

    inFile = fopen("input.txt", "r");
    fscanf(inFile, "%d%d%d", numbers, numbers + 1, numbers + 2);
    while(i++ < 3)
        printf("THE %d NUMBER: %5d\n", i, numbers[i - 1]);
    fclose(inFile);

    outFile = fopen("output.txt", "w");
    fprintf(outFile, "%d %d %d\n", numbers[1], numbers[0], numbers[2]);
    fclose(outFile);

    return 0;
}
