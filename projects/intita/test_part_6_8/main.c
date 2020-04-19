/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Заняття 6. Текстові файли.
 * Частина 8. Введення-виведення даних текстових файлів у рядкові змінні.
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 26.05.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.2.1 Основан на Qt 5.3.2 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/* ЗАВДАННЯ
Реалізуй програму, яка б виконувала наступні дії:
1) читання з файлу input.txt рядків по словах;
2) перевірку кожного прочитаного слова на наявність серед його символів цифр;
3) запис слів з цифрами в інший файл (output.txt).
*/

#include <stdio.h>
#include <conio.h>
#define MAX_STRING_LENGTH 80

int scanWordsWithFigures(FILE *, FILE *);

int main(void)
{
    FILE * inFile = NULL;
    FILE * outFile = NULL;
    int words_count = 0;

    //inFile = fopen("input.txt", "w");
    //fclose(inFile);
    //return 0;

    inFile = fopen("input.txt", "r");
    if(!inFile)
    {
        puts("INPUT FILE DOES NOT EXIST!");
        getch();
        return 0;
    }

    outFile = fopen("output.txt", "w");
    if(!outFile)
    {
        puts("OUT FILE CAN NOT BE CREATED!");
        fclose(inFile);
        getch();
        return 0;
    }

    words_count = scanWordsWithFigures(inFile, outFile);
    printf("\n");
    printf("THERE ARE %d WORDS WITH FIGURES!\n", words_count);

    fclose(inFile);
    fclose(outFile);

    getch();
    return 0;
}

int scanWordsWithFigures(FILE * inFile, FILE * outFile)
{
    char word[MAX_STRING_LENGTH + 1] = "";
    char * ptr_word = NULL;
    int words_count = 0;
    int i = 0;

    while(fscanf(inFile, "%s", word) == 1)
    {
        printf("THE %2d WORD: %20s", ++i, word);
        ptr_word = word;
        do
        {
            if(*ptr_word >= '0' && *ptr_word <= '9')
            {
                printf(" -> output.txt");
                fprintf(outFile, "%s\n", word);
                words_count++;
                break;
            }
        }
        while(*ptr_word++);
        printf("\n");
    }

    return words_count;
}
