#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define STR_NUMBER_MAX_LEN 10
#define STR_MAX_LEN        80

typedef enum in_sequence
{
    NOT,
    IS_NUMBER,
    IS_STRING,
    IN_SEQUENCE_END
} eInSqc;

typedef struct legend
{
    char   str_number[STR_NUMBER_MAX_LEN + 1];
    eInSqc in_sequence;
} sLegend;

void getLegend(sLegend * legend, char * str_sequence, char * file_name);
void mf_openFile(char * file_name, char * file_mode, FILE ** file_ptr_addr);

//ПРИПУЩЕННЯ
//-числа в LEGEND виводяться ПОСЛІДОВНО від МЕНШОГО до БІЛЬШОГО очинаючи з НУЛЯ

int main(void)
{


    int       numbers_count                      = 11;
    sLegend * legend                             = NULL;
    char      str_sequence[STR_MAX_LEN + 1]      = {};
    char    * str_seq_ptr                        = str_sequence;
    char      str_number[STR_NUMBER_MAX_LEN + 1] = {};
    int       int_number                         = 0;
    int       i                                  = 0;
    char    * inp_file_name                      = "input.md.txt";

    legend = (sLegend *)calloc(numbers_count, sizeof(sLegend));

    //читаємо файл заповнюємо масив
/*  zero 0
    one 1
    two 2
    three 3
    four 4
    five 5
    six 6
    seven 7
    eight 8
    nine 9
    ten 10 */

    //читаємо файл заповнюємо змінну
    getLegend(legend, str_sequence, inp_file_name);

    //читаємо попередню змінну заповнюємо масив
    while( sscanf(str_seq_ptr, "%s", str_number) > 0)
    {
        //printf("%s!\n%s!\n%d\n", str_seq_ptr, str_number, int_number);
        str_seq_ptr += strlen(str_number) + 1;
        int_number = 0;
        if( str_number[0] == '0' || (int_number = atoi(str_number)) )
        {
            if( !legend[int_number].in_sequence )
                legend[int_number].in_sequence = IS_NUMBER;
            //printf("%d\n", int_number);
        }
        else
        {
            for( i = 0; i < numbers_count; i++ )
            {
                if( !strcmp(legend[i].str_number, str_number) )
                {
                    if( !legend[i].in_sequence )
                        legend[i].in_sequence = IS_STRING;
                    //printf("%s\n", str_number);
                    break;
                }
            }
        }
    }

    //формуємо вихідний файл
    for(i = 0; i < numbers_count; i++)
    {
        if( legend[i].in_sequence )
        {
            if( legend[i].in_sequence == IS_NUMBER )
                printf("%d ", i);
            else
                printf("%s ", legend[i].str_number);
        }
    }

    puts("\nEND\n");
    return 0;
}

void getLegend(sLegend * legend, char * str_sequence, char * inp_file_name)
{
    FILE * input_file;
    char   string[STR_MAX_LEN + 1] = "";
    int    number;
    char   str_number[STR_NUMBER_MAX_LEN + 1] = "";

    mf_openFile(inp_file_name, "r", &input_file);

    if( !input_file  ) exit(0);

    while( fgets(string, STR_MAX_LEN + 1, input_file) )
    {
        if( strstr(string, "#Sequence#") )
        {
           while( fgets(string, STR_MAX_LEN + 1, input_file) )
           {
               if( strlen(string) ) strcpy(str_sequence, string);
           }
        }
        else if( sscanf(string, "%s%d", str_number, &number) == 2 )
        {
            strcpy(legend[number].str_number, str_number);
            //printf("%s\n", str_number);
        }
    }
}

void mf_openFile(char * file_name, char * file_mode, FILE ** file_ptr_addr)
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
        case 'a':
        case 'w':
            printf("CAN NOT OPEN OR CREATE FILE %s !\n", file_name);
            break;
    }
}

