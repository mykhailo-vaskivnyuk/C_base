#include "my_functions.h"

void mf_OpenFile(char * file_name, char * file_mode, FILE ** file_ptr_addr)
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
            printf("CAN NOT OPEN OR CREATE FILE %s!\n", file_name);
            break;
    }
}

int mf_Rnd(int range_min_value, int range_max_value)
{
    return (double)rand() / 32767 * (range_max_value - range_min_value) + range_min_value + 0.5;
}

void mf_StrCut(char * string, char * string_cut)
{
    char * string_cut_pos;

    if( (string_cut_pos = strstr(string, string_cut)) )
        *string_cut_pos = '\0';
}

bool mf_StrRplEnd(char * string, char * string_end, char * string_rpl)
{
    int str_len     = strlen(string);
    int str_end_len = strlen(string_end);

    if( str_len < str_end_len ) return false;
    if( strcmp(string + str_len - str_end_len, string_end) != 0 ) return false;

    strcpy(string + str_len - str_end_len, string_rpl);
    return true;
}

int mf_ReadFile(char * file_name, char * array, int array_size_N, int array_size_M)
{
    FILE * input_file = NULL;
    int counter       = 0;

    mf_openFile(file_name, "r", &input_file);
    if( input_file == NULL ) return -1;
    for(counter = 0;
        counter < array_size_N && fgets(array + counter * array_size_M, array_size_M, input_file);
        counter++)
        mf_StrCut(array + counter * array_size_M, "\n");
    fclose(input_file);
    return counter;
}

