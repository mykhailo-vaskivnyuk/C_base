/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Заняття 6. Текстові файли.
 * Частина 9. Підсумкове завдання.
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 29.05.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.2.1 Основан на Qt 5.3.2 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/* ЗАВДАННЯ
1. Створіть текстовий файл, в якому в довільному порядку записані цілі і дійсні числа
   (ціла і дробова частина відділяються символом “.”);
2. Напишіть програму, яка здійснює обробку даного файлу і аналіз його даних наступним чином:
   а) читає послідовно з файлу числа і розподіляє їх для запису в два інші файли:
      перший - лише цілі, другий - лише дійсні;
   б) числа в нові файли повинні записуватись в стовпчик;
   в) останнім рядком кожного файлу має бути: “Сума = S”, де S - сума всіх чисел файлу;
3. Для файлу дійсних чисел виконайте додаткову обробку:
   а) виділіть цілі частини кожного числа;
   б) допишіть в кінці файлу рядок: “Цілі частини: ...” - і далі в один рядок
      (через пробіли) запишіть виділені значення;
   в) останнім рядком у файлі дійсних чисел зробіть наступний:
      “Сума цілих частин = Sс”, де Sс - сума відповідних значень.
*/

#include <stdio.h>
#include <conio.h>
    //getch()
#include <string.h>
    //strstr()
#include <stdlib.h>
    //atoi()
    //atof()
#include <unistd.h>
    //sleep()

#define MAX_STRING_LENGTH 80

int sortIntFlt(FILE *, FILE *, FILE *); //write integer and float numbers into different files
int writeFltToInt(FILE *, FILE *); //write integer parts of float numbers into float output file

int main(void)
{
    FILE * inFile = NULL;
    FILE * outFileInt = NULL; //file for integer numbers
    FILE * outFileFlt = NULL; //file for float numbers
    int numbers_count = 0;

//    inFile = fopen("input.txt", "w");
//    fclose(inFile);
//    return 0;

    inFile = fopen("input.txt", "r");
    if(!inFile)
    {
        puts("INPUT FILE DOES NOT EXIST!");
        getch();
        return 0;
    }

    outFileInt = fopen("output_integer.txt", "w");
    if(!outFileInt)
    {
        puts("OUT FILE FOR INTEGER NUMBERS CAN NOT BE CREATED!");
        fclose(inFile);
        getch();
        return 0;
    }

    outFileFlt = fopen("output_float.txt", "w");
    if(!outFileFlt)
    {
        puts("OUT FILE FOR FLOAT NUMBERS CAN NOT BE CREATED!");
        fclose(inFile);
        fclose(outFileInt);
        getch();
        return 0;
    }

/*----------------------------------------------------------------
    sort integer and float numbers into differnt files
----------------------------------------------------------------*/
    numbers_count = sortIntFlt(inFile, outFileInt, outFileFlt);
    printf("\n");
    printf("THERE ARE %d NUMBERS HAVE BEEN SORTED!\n", numbers_count);
    fclose(outFileInt);
/*----------------------------------------------------------------
    write integer part of float numbers into float output file
----------------------------------------------------------------*/
    rewind(inFile);
    fprintf(outFileFlt, "\n");
    printf("\n");
    numbers_count = writeFltToInt(inFile, outFileFlt);
    printf("\n");
    printf("THERE ARE %d FLOAT NUMBERS HAVE BEEN WRITTEN!\n", numbers_count);
    fclose(inFile);
    fclose(outFileFlt);

    getch();
    return 0;
}

int sortIntFlt(FILE * inFile, FILE * outFileInt, FILE * outFileFlt)
{
    char    number_str[MAX_STRING_LENGTH + 1] = "";
    int     numbers_count = 0;
    int     number_int = 0;
    float   number_flt = 0;
    int     sum_int = 0;
    float   sum_flt = 0;

    while( fscanf(inFile, "%s", number_str) == 1 )
    {
        printf("THE %2d NUMBER: %20s", ++numbers_count, number_str);
        if( !strstr(number_str, ".") && !strstr(number_str, "e") && !strstr(number_str, "E"))
        {
            puts(" -> output_int.txt");
            number_int = atoi(number_str);
            sum_int += number_int;
            fprintf(outFileInt, "%16d\n", number_int);
        }
        else
        {
            puts(" -> output_flt.txt");
            number_flt = atof(number_str);
            sum_flt += number_flt;
            fprintf(outFileFlt, "%21f\n", number_flt);
        }
    }
    printf("\n");
    printf("Sum Int = %d\n", sum_int);
    printf("Sum Flt = %f\n", sum_flt);
    fprintf(outFileInt, "Sum = %10d\n", sum_int);
    fprintf(outFileFlt, "Sum = %15f\n", sum_flt);
    fflush(outFileInt);
    fflush(outFileFlt);
    return numbers_count;
}

int writeFltToInt(FILE * inFile, FILE * outFileFlt)
{
    char    number_str[MAX_STRING_LENGTH + 1] = "";
    int     numbers_count = 0;
    int     number_int = 0;
    int     sum_int = 0;

    while( fscanf(inFile, "%s", number_str) == 1 )
    {
        if( strstr(number_str, ".") )
        {
            printf("THE %2d NUMBER: %20s", ++numbers_count, number_str);
            puts(" -> output_flt.txt flt -> int");
            number_int = (int)atof(number_str);
            sum_int += number_int;
            fprintf(outFileFlt, "%d ", number_int);
        }
    }
    printf("\n");
    printf("Sum Int fo Flt = %d\n", sum_int);
    fprintf(outFileFlt, "\n");
    fprintf(outFileFlt, "Sum Int = %4d\n", sum_int);
    fflush(outFileFlt);
    return numbers_count;
}
