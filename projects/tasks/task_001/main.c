#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#define ARRAY_SIZE_N 4
#define ARRAY_SIZE_M 4
#define STR_MAX_LEN  80

void   funcTest001  (int    mode);
char * setArrayPrint(int  * array,      int  * value,        char * str_value,    int row,        int column);
int    inputNumber  (char * inpur_text, bool(* condition)(), int    min_value,    int max_value);
bool   checkNumber  (int    number,     int    min_value,    int    max_value);

int main(void)
{
//-- оголошуємо змінні--------------------------------------------------------//
    bool          running                   = true;
    int           mode                      = 0;
                  // 0 | 2 - запуск/перезапуск основної функції (в ручному | автоматичному) режимах
                  // 1     - продовження роботи основної функції: ввід з клавіатури
                  // 3     - продовження роботи основної функції: автоматично
                  //-1     - завершення роботи основної функції
//----------------------------------------------------------------------------//
    while( running )
    {
        puts("\0");
//-- виконуємо основну функцію -----------------------------------------------//
        funcTest001(mode);
//-- виводимо меню для продовження, завершення, перезапуску або зміни режиму--//
        puts("\0");
        printf("  %-38s", "[ENTER    ] - CONTINUE");
        printf("%-38s", "[BACKSPACE] - RESTART");
        puts("\n");
        printf("  %-38s", "[TAB      ] - AUTO | MANUAL");
        printf("%-38s", "[OTHER KEY] - EXIT");
        puts("\n");
        switch( getch() )
        {
            case '\r':                      // [ENTER    ]
                mode = mode | 1;
                continue;
            case '\b':                      // [BACKSPACE]
                mode = mode & 2;
                break;
            case '\t':                      // [TAB      ]
                mode = (mode | 1) ^ 2;
                break;
            default:                        // [ANY KEY  ]
                funcTest001(-1);
                running = false;
        }
    }

    return 0;
}

void funcTest001(int mode)
{
    static bool   start     = true;
    static int  * array;
    static int    free_cells;
    static char * screen_buffer;
    static bool   auto_mode = false;

    int  array_size               = ARRAY_SIZE_N * ARRAY_SIZE_M;
    int  value                    = 0;
    int  index                    = 0;
    char str_tmp[STR_MAX_LEN + 1] = "";

//-- звільняємо пам'ять перед завершенням роботи функції ---------------------//
    if( mode ==  -1)
    {
        free(screen_buffer);
        free(array);
        return;
    }
//-- при першому запуску виділяємо пам'ять -----------------------------------//
    if( !(mode & 1) ) start = true;

    if( start )
    {
        free(screen_buffer);
        free(array);
        free_cells = array_size;

        array = (int *)calloc(array_size, sizeof(int));
        screen_buffer = setArrayPrint(NULL, NULL, NULL, ARRAY_SIZE_N, ARRAY_SIZE_M);

        auto_mode = mode & 2;
    }
//-- цикл заповнення масиву --------------------------------------------------//
    while( free_cells )
    {
        if( start )
        {
           start = false;
           break;
        }

        if( auto_mode != (bool)(mode & 2) )
        {
            auto_mode = (bool)(mode & 2);
            break;
        }
//-- ввід даних з клавіатури або автоматично ---------------------------------//
        if( mode & 2 )
        {
            index = (array_size - 0.01) * (float)rand() / 32768;
            value  = 99.99 * (float)rand() / 32768 + 1;
        }
        else
        {
            sprintf(str_tmp, "INPUT INDEX OF ROW FROM 0 TO %d: ", ARRAY_SIZE_N - 1);
            index = inputNumber(str_tmp, checkNumber, 0, ARRAY_SIZE_N - 1) * ARRAY_SIZE_N;
            sprintf(str_tmp, "INPUT INDEX OF COLUMN FROM 0 TO %d: ", ARRAY_SIZE_M - 1);
            index += inputNumber(str_tmp, checkNumber, 0, ARRAY_SIZE_M - 1);
            sprintf(str_tmp, "INPUT INTEGER NUMBER FROM 0 TO 99: ");
            value = inputNumber(str_tmp, checkNumber, 0, 99);
        }

        while( array[index] != 0 )
        {
            system("cls");
            puts(setArrayPrint(NULL, NULL, "", index / ARRAY_SIZE_M, index % ARRAY_SIZE_M));
            Sleep(400);

            system("cls");
            puts(setArrayPrint(NULL, &array[index], NULL, index / ARRAY_SIZE_M, index % ARRAY_SIZE_M));
            Sleep(400);

            system("cls");
            puts(setArrayPrint(NULL, NULL, "", index / ARRAY_SIZE_M, index % ARRAY_SIZE_M));
            Sleep(400);

            system("cls");
            puts(setArrayPrint(NULL, &array[index], NULL, index / ARRAY_SIZE_M, index % ARRAY_SIZE_M));
            Sleep(400);
//****************************************************************************//
//      РІШЕННЯ TEST 1
//****************************************************************************//
            if( (index += ARRAY_SIZE_M) > array_size - 1 )
                if( (index -= array_size - 1) > ARRAY_SIZE_M - 1 ) index = 0;
        }

        array[index] = value;
//****************************************************************************//
//      END РІШЕННЯ TEST 1
//****************************************************************************//

        setArrayPrint(NULL, &value, "", index / ARRAY_SIZE_M, index % ARRAY_SIZE_M);
        free_cells--;
        break;
    }

    system("cls");
    puts(screen_buffer);

    printf("\n                    MODE: ");
    if( auto_mode )
        printf("AUTO\n");
    else
        printf("MANUAL\n");

    if( free_cells )
        printf("\n                    REST: %d\n\n", free_cells);
    else
        printf("\n                    ARRAY IS FULL!\n\n");

}

char * setArrayPrint(int * array, int * value, char * str_value, int row, int column)
{
/*    МАКЕТ ТАБЛИЦІ 4х4
      ........................\n
      ........................\n
      ........................\n
      ...---------------------\n
      ...|      1   2   3   4 \n
      ...|   -----------------\n
      ...|  1|   |   |   |   |\n
      ...|   |---|---|---|---|\n
      ...|  2|   |   |   |   |\n
      ...|   |---|---|---|---|\n
      ...|  3|   |   |   |   |\n
      ...|   |---|---|---|---|\n
      ...|  4|   |   |   |   |\n
      ...-   -----------------\0
*/
#define bN buf_size_N
#define bM buf_size_M
#define mT top_margin
#define mL left_margin
#define R  row
#define C  column
#define CW cell_width

    static char * buffer;
    static int buf_size_N;
    static int buf_size_M;

    int  left_margin     = 15;
    int  top_margin      = 5;
    int  cell_width      = 3;

    char format_int[5]   = "";
    char format_str[5]   = "";
    int  i               = 0;
    int  j               = 0;
    char str_tmp[CW + 1];

    sprintf(format_int, "%c%dd", '%', CW);
    sprintf(format_str, "%c%ds", '%', CW);

    if ( array == NULL && value == NULL && str_value == NULL ) {
        if( !R || !C )
        {
            free(buffer);
            return NULL;
        }

        bN = mT + R *  2            + 3;
        bM = mL + C * (CW + 1) + CW + 3;
        buffer = (char *)calloc(bN * bM, sizeof(char));
        memset(buffer, ' ', bN * bM);
//----- в кінці кожного рядка вставляємо \n ------------------------------------
        for (i = 0; i < bN; i++) buffer[(i + 1) * bM - 1] = '\n';
        buffer[bN * bM - 1] = '\0';
//----- формуємо підписи колонок -----------------------------------------------
        for (i = 0; i < C; i++)
        {
            sprintf(str_tmp, format_int, i + 1);
            memcpy(&buffer[(mT + 1) * bM + mL + CW + 2 + i * (CW + 1)]
                  , str_tmp
                  , CW);
        }
        memset(&buffer[(mT + 2) * bM + mL + CW + 1]
              , '-', bM - mL - CW - 2);
//----- формуємо підписи рядків ------------------------------------------------
        for (i = 0; i < R; i++)
        {
            sprintf(str_tmp, format_int, i + 1);
            memcpy(&buffer[(i * 2 + mT + 3) * bM + mL + 1]
                  , str_tmp
                  , CW);
            buffer[(i * 2 + mT + 3) * bM + mL + 1 + CW] = '|';
            buffer[(i * 2 + mT + 4) * bM + mL + 1 + CW] = '|';
        }
//----- формуємо лінії таблиці--------------------------------------------------
        for (i = 0; i < R; i++)
        {
            for (j = 0; j < C; j++)
            {
                        buffer[(i * 2 + mT + 3) * bM + mL + CW + 2 + j * (CW + 1) + CW] = '|';
                memset(&buffer[(i * 2 + mT + 4) * bM + mL + CW + 2 + j * (CW + 1)]
                      , '-', CW);
                        buffer[(i * 2 + mT + 4) * bM + mL + CW + 2 + j * (CW + 1) + CW] = '|';
            }
        }
        memset(&buffer[(bN - 1) * bM + mL + 1 + CW], '-', (CW + 1) * C + 1);

        return buffer;
    }

    if ( value != NULL || str_value != NULL )
    {
        if( value != NULL )
            sprintf(str_tmp, format_int, *value);
        else
            sprintf(str_tmp, format_str, str_value);

        memcpy(&buffer[(R * 2 + mT + 3) * bM + C * (CW + 1) + mL + CW + 2]
              , str_tmp
              , CW);
    }

    return buffer;

#undef bN
#undef bM
#undef mT
#undef mL
#undef R
#undef C
#undef CW
 }

int inputNumber(char * input_text, bool (*condition)(), int min_value, int max_value)
{
    int input_number = 0;
    while( 1 )
    {
        printf(input_text);
        fflush(stdin);
        input_number = 0;
        scanf("%d", &input_number);
        if( condition(input_number, min_value, max_value) ) break;
        puts("WRONG NUMBER. TRY AGAIN!");
    }
    return input_number;
}

bool checkNumber(int number, int min_value, int max_value)
{
    if( number >= min_value && number <= max_value )
        return true;
    return false;
}
