/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Заняття 7. Файли з довільним доступом.
 * Частина 4. Читання і запис бінарних файлів.
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 01.06.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.2.1 Основан на Qt 5.3.2 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/* ЗАВДАННЯ
   Підготуй двійковий файл input.dat, що містить деяку кількість цілих чисел.
   Реалізуй програму для виконання наступних дій:
1) оголосити два масиви цілих чисел різної розмірності (наприклад, A[N] і B[M]);
2) дані з двійкового файлу спочатку прочитати в масив A[N] ;
   масив B[M] попередньо заповнюється нулями;
3) якщо даних у файлі більше, ніж розмірність N - залишок даних записати в масив B[M] ;
4) якщо даних у файлі більше, ніж сукупна розмірність обох масивів -
   видається повідомлення про помилку і вихід з програми;
5) у двійковий файл output.dat записати послідовно числа - суми відповідних елементів
   (під однаковими номерами) масивів A[N] і B[M]
   (надлишкові елементи одного з масивів, якщо такі будуть - проігнорувати);
6) вивести на екран вміст обох масивів, а також дані з файлу output.dat,
   перевірити результати на коректність.
*/

#include <stdio.h>
#include <stdlib.h>
    //rand()

#define NUMBERS_COUNT 15
#define N 10
#define M 14

char createInputFile(char *);
void array_print(int *, int);
void openFile(char *, char *, FILE **);

int main(void)
{
    FILE * inFile = NULL;
    FILE * outFile = NULL;
    char * file_name_in = "input.dat";
    char * file_name_out = "output.dat";
    size_t int_size = sizeof(int);
    int array_N[N]= {};
    int array_M[M] = {};
    int numbers_count = 0;
    int numbers_count_2 = 0;
    int i = 0;
//------------------------------------------------------------------------------
    if( !createInputFile(file_name_in) ) return 0;
//------------------------------------------------------------------------------
    openFile(file_name_in, "rb", &inFile);
    if( !inFile ) return 0;

    numbers_count = fread(array_N, int_size, N, inFile);
    numbers_count_2 = fread(array_M, int_size, M, inFile);
    numbers_count += numbers_count_2;

    if( numbers_count == N + M && fgetc(inFile) != EOF)
    {
        printf("THERE ARE VERY MANY NUMBERS IN FILE %s !\n", file_name_in);
        fclose(inFile);
        return 0;
    }

    fclose(inFile);
//------------------------------------------------------------------------------
    puts("\n-------THE FIRST ARRAY-------\n");
    array_print(array_N, N);
    printf("\n");
    puts("-------THE SECOND ARRAY------\n");
    array_print(array_M, M);
    printf("\n");
    if(numbers_count_2 == 0)
    {
        puts("AS SECOND ARRAY IS EMPTY DATA INTO OUTPUT FILE ARE NOT WRITTEN!\n");
        return 0;
    }
//------------------------------------------------------------------------------
    if( N < M && N < numbers_count_2) numbers_count_2 = N;
    for(i = 0; i < numbers_count_2; i++) array_M[i] += array_N[i];
//------------------------------------------------------------------------------
    openFile(file_name_out, "wb+", &outFile);
    if( !outFile ) return 0;

    fwrite(array_M, int_size * numbers_count_2, 1, outFile);
    fflush(outFile);

    puts("-------THE THIRD ARRAY-------\n");
    rewind(outFile);
    while( fread(&i, int_size, 1, outFile) ) printf("%4d", i);
    puts("\n");

    fclose(outFile);
//------------------------------------------------------------------------------
    return 0;
}
/***********************************************************
    FUNCTIONS
***********************************************************/
char createInputFile(char * file_name)
{
    FILE * new_file;
    int number;
    size_t int_size = sizeof(int);
    int i = 0;

    openFile(file_name, "wb", &new_file);
    if(!new_file) return 0;

    for(i = 0; i < NUMBERS_COUNT; i++)
    {
        number = rand() & 255;
        fwrite(&number, int_size, 1, new_file);
    }

    fclose(new_file);

    return 1;
}
//------------------------------------------------------------------------------
void array_print(int * array, int array_size)
{
    int i = 0;

    while( i++ < array_size ) printf("  %02d", i);

    printf("\n");

    while( array_size-- ) printf("%4d", *array++);

    printf("\n");
}
//------------------------------------------------------------------------------
void openFile(char * file_name, char * file_mode, FILE ** file_ptr_addr)
{    
    *file_ptr_addr = fopen(file_name, file_mode);

    if( *file_ptr_addr )
    {
        rewind(*file_ptr_addr);
        return;
    }

    switch( *file_mode )
    {
        case 'r':
            printf("FILE %s DOES NOT EXIST!\n", file_name);
            break;
        case 'w':
            printf("CAN NOT OPEN OR CREATE FILE %s !\n", file_name);
            break;
    }
}
//------------------------------------------------------------------------------
