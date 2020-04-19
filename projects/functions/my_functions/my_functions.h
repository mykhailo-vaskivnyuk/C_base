#ifndef MY_FUNCTIONS
#define MY_FUNCTIONS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void mf_OpenFile (char * file_name, char * file_mode, FILE ** file_ptr_addr);
int  mf_ReadFile (char * file_name, char * array, int array_size_N, int array_size_M);

int  mf_Rnd      (int range_min_value, int range_max_value);

void mf_StrCut   (char * string, char * string_cut);
bool mf_StrRplEnd(char * string, char * string_end, char * string_rpl);

#endif //MY_FUNCTIONS
