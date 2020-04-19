#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#define array_size_N     12
#define array_size_M     8
#define ISTOTA_MIN_VALUE 1
#define ISTOTA_MAX_VALUE 90
#define SRAND            6000

/*             5 X 5
   -----------------------------
   | X | X | X | X | X | X | X |
   |---------------------------|
   | X |   |   |   |   |   | X |
   |---|---|---|---|---|---|---|
   | X |   |   |   |   |   | X |
   |---|---|---|---|---|---|---|
   | X |   |   |   |   |   | X |
   |---|---|---|---|---|---|---|
   | X |   |   |   |   |   | X |
   |---|---|---|---|---|---|---|
   | X |   |   |   |   |   | X |
   |---------------------------|
   | X | X | X | X | X | X | X |
   -----------------------------
*/

typedef struct istota
{
    bool fresh;
    int  power;

} sIstota;

typedef struct game_field
{
    int        field_size_N;
    int        field_size_M;
    int        field_size;
    int        field_allow_size;
    int        free_cells;
    int        new_count;
    int        bat_count;
    sIstota *  field;
    sIstota ** ptr_field;
    char    *  screen_buffer;

} sGameField;

//-- FUNCTIONS -----------------------------------------------------------------
void gmfd_init      (sGameField * game_field);
void gmfd_new_select(sIstota * istota);
void gmfd_bat_select(sIstota * istota);
void gmfd_new_put   ();
void gmfd_bat_run   ();
void gmfd_scan      (void (*action)(sIstota * istota));
int  rnd            (int range_min_value, int range_max_value);
void gmfd_print     ();
int  gmfd_index_set (int index, int direction);
char * setArrayPrint(int * array, int * value, char * str_value, int row, int column);
bool ifMin          (int a, int b);
void gmfd_sort      (sIstota ** istoty, int istoty_count, bool (*condition)(int, int));
//-- END FUNCTIONS -------------------------------------------------------------

static sGameField * GAME_FIELD;

int main(void)
{
    srand(SRAND);
    sGameField game_field;
    gmfd_init(&game_field);

    do
    {
        //народження
        gmfd_new_put();
            //народжують ті, хто народився на попередньому циклі
                    //на першому циклі істота народжується ні від кого
                //rnd нової істоти (потомка) 1...99
                //rnd кількість потомків     1...8
                    //на першому циклі народжується 1-а істота
                //rnd місце народження       1...8
                //                           (
                //                            left,      right,
                //                            up, down,
                //                            left_up,   right_up,
                //                            left_down, right_down
                //                           )
                //                           відносно пращура в діапазоні
                //                           [0...(N-1)][0...(M-1)]
                    //на першому циклі місце народження
                    //                       [0...(N-1)][0...(M-1)]
                //пращур збільшується на кількість ненароджених
        gmfd_print();

        //знищення
        gmfd_bat_run();
            //хто пройшов етап народження і парний
            //пріоритет в слабшого
            //рівні не знищуються
        gmfd_print();

    }while( game_field.free_cells || game_field.new_count );

    return 0;
}

void gmfd_init(sGameField * game_field)
{
    GAME_FIELD = game_field;

    game_field->field_size_N       = array_size_N + 2;
    game_field->field_size_M       = array_size_M + 2;
    game_field->field_size         = game_field->field_size_N * game_field->field_size_M;
    game_field->field_allow_size   = array_size_N * array_size_M;
    game_field->free_cells         = game_field->field_allow_size;
    game_field->new_count          = 0;
    game_field->bat_count          = 0;
    game_field->field              = (sIstota *)calloc(game_field->field_size, sizeof(sIstota));
    game_field->ptr_field          = (sIstota **)calloc(game_field->field_allow_size, sizeof(sIstota *));

    game_field->screen_buffer      = setArrayPrint(NULL, NULL, NULL, game_field->field_size_N
                                                   , game_field->field_size_M);

    int i     = 0;
    int j     = 0;
    int power = -1;

    for(i = 0; i < game_field->field_size_N; i++)
    {
        for(j = 0; j < game_field->field_size_M; j++)
        {
            if(i == 0 ||
               i == game_field->field_size_N - 1 ||
               j == 0 ||
               j == game_field->field_size_M - 1)
            {
                (game_field->field)[i * game_field->field_size_M + j].power = power;
                (game_field->field)[i * game_field->field_size_M + j].fresh = false;
                setArrayPrint(NULL, NULL, "|||||", i, j);
            }
        }
    }
}

void gmfd_print()
{
    sGameField * game_field = GAME_FIELD;
    system("cls");
    puts("\n\n");
    printf("                free   > %2d\n", game_field->free_cells);
    printf("                new    > %2d\n", game_field->new_count);
    printf("                battle > %2d\n", game_field->bat_count);
    puts(game_field->screen_buffer);
    //getch();
    Sleep(400);
}

int rnd(int range_min_value, int range_max_value)
{
    return (double)rand() / 32767 * (range_max_value - range_min_value) + range_min_value + 0.5;
}

void gmfd_new_put()
{
    sGameField *  game_field  = GAME_FIELD;
    sIstota    ** ptr_field   = GAME_FIELD->ptr_field;

    int index                 = 0;
    int index_new             = -1;
    int i                     = 0;
    int j                     = 0;
    int k                     = 0;
    int new_count             = 0; //1...8
    sIstota * free_for_new[8] = {};

    memset(ptr_field, 0, game_field->field_allow_size * sizeof(sIstota *));

    //вибираємо всіх нових в **
    gmfd_scan(gmfd_new_select);

    if( (game_field->ptr_field)[0] == NULL )
    {
        do
        {
            index_new = gmfd_index_set( rnd( game_field->field_size_M + 1
                                  , game_field->field_size - game_field->field_size_M - 1)
                             , 0);
        }while( index_new == -1 || game_field->field[index_new].power );

        game_field->field[index_new].power = rnd(ISTOTA_MIN_VALUE, ISTOTA_MAX_VALUE);
        game_field->field[index_new].fresh = true;
        game_field->free_cells -= 1;
        game_field->new_count += 1;
        setArrayPrint(NULL, &(game_field->field[index_new].power), "N"
                          , index_new / game_field->field_size_M
                          , index_new % game_field->field_size_M);
        return;
    }

    //виконуємо перебір всіх нових, кожен з них народжує
    while( (game_field->ptr_field)[i] )
    {
        index = (game_field->ptr_field)[i] - game_field->field;
        new_count = rnd(1, 8);

        k = 0;
        for(j = 1; j <= 8; j++)
        {
            if( (index_new = gmfd_index_set(index, j)) == -1 ) continue;
            if( (game_field->field)[index_new].power != 0 ) continue;
            free_for_new[k] = &(game_field->field)[index_new];
            k++;
        }

        if( new_count > k )
        {
            (game_field->ptr_field)[i]->power += new_count - k;
            new_count = k;
        }
        else if( new_count < k)
        {
            for(j = 0; j < k - new_count; j++)
            {
                do
                {
                    index_new = rnd(0, k - 1);
                }while( free_for_new[index_new] == NULL );
                free_for_new[index_new] = NULL;
            }
        }

        k = 0;
        for(j = 0; j < new_count; j++)
        {
            while( free_for_new[k] == NULL ){ k++; }
            index_new = free_for_new[k] - game_field->field;
            free_for_new[k]->power = rnd(ISTOTA_MIN_VALUE, ISTOTA_MAX_VALUE);
            free_for_new[k]->fresh = true;
            game_field->free_cells -= 1;
            game_field->new_count += 1;
            setArrayPrint(NULL, &(free_for_new[k]->power), "N"
                              , index_new / game_field->field_size_M
                              , index_new % game_field->field_size_M);
            k++;
            gmfd_print();
        }
        (game_field->ptr_field)[i]->fresh  = false;
        setArrayPrint(NULL, &((game_field->ptr_field)[i]->power), NULL
                          , index / game_field->field_size_M
                          , index % game_field->field_size_M);
        game_field->new_count -= 1;
        if( !((game_field->ptr_field)[i]->power % 2) )
        {
            setArrayPrint(NULL, NULL, "A"
                              , index / game_field->field_size_M
                              , index % game_field->field_size_M);
        }

        i++;
    }
}

void gmfd_bat_run()
{
    sGameField *  game_field = GAME_FIELD;
    sIstota    ** ptr_field  = GAME_FIELD->ptr_field;

    int index     = 0;
    int i         = 0;
    int j         = 0;
    int neighbor  = 0;

    memset(ptr_field, 0, game_field->field_allow_size * sizeof(sIstota *));
    game_field->bat_count = 0;

    //вибираємо всіх агресивних в **
    gmfd_scan(gmfd_bat_select);

    if( game_field->bat_count < 2 ) return;

    //сортування
    gmfd_sort(game_field->ptr_field, game_field->bat_count, ifMin);

    //виконуємо перебір всіх агресивних, кожен з них вступає в боротьбу з сусідом
    do
    {
        j = i + 1;
        do
        {
            if( !(game_field->ptr_field)[i]->power ) break;
            if( !(game_field->ptr_field)[j]->power ) continue;

            //визначити чи в сусдніх комірках...
            neighbor = abs((game_field->ptr_field)[i] - (game_field->ptr_field)[j]);
            if( neighbor != 1)
            {
                neighbor = abs(neighbor - game_field->field_size_M);
                if( neighbor > 1) continue;
            }

            if( (game_field->ptr_field)[i]->power == (game_field->ptr_field)[j]->power )
                continue;
            if( (game_field->ptr_field)[i]->power > (game_field->ptr_field)[j]->power )
            {
                (game_field->ptr_field)[j]->power = 0;
                (game_field->ptr_field)[j]->fresh = false;
                index = (game_field->ptr_field)[j] - game_field->field;
            }
            else
            {
                (game_field->ptr_field)[i]->power = 0;
                (game_field->ptr_field)[i]->fresh = false;
                index = (game_field->ptr_field)[i] - game_field->field;
            }
            game_field->free_cells += 1;
            setArrayPrint(NULL, &(game_field->field[index].power), "     "
                              , index / game_field->field_size_M
                              , index % game_field->field_size_M);
            gmfd_print();
        }while( (game_field->ptr_field)[++j] );
    }while( (game_field->ptr_field)[++i + 1] );
}

void gmfd_scan(void (*action)(sIstota * istota))
{
    sGameField * game_field = GAME_FIELD;
    int          index      = 0;
    int          i          = 0;
    int          j          = 0;

    for(i = 1; i < game_field->field_size_N - 1; i++)
    {
        for(j = 1; j < game_field->field_size_M - 1; j++)
        {
            index = i * game_field->field_size_M + j;
            action(&(game_field->field)[index]);
        }
    }
}

void gmfd_new_select(sIstota * istota)
{
    sGameField * game_field = GAME_FIELD;
    if(istota->fresh == false) return;
    int i = 0;

    while( (game_field->ptr_field)[i] != NULL ){ i++; }
    (game_field->ptr_field)[i] = istota;
}

void gmfd_bat_select(sIstota * istota)
{
    sGameField * game_field = GAME_FIELD;

    if( !istota->power )     return;
    if(  istota->fresh )     return;
    if(  istota->power % 2 ) return;

    int i = 0;

    while( (game_field->ptr_field)[i] != NULL ){ i++; }
    (game_field->ptr_field)[i] = istota;
    game_field->bat_count += 1;
}

int gmfd_index_set(int index, int direction)
{
    // direction
    // 0 -
    // 1 - left-up
    // 2 - up
    // 3 - right-up
    // 4 - right
    // 5 - right-down
    // 6 - down
    // 7 - left-down
    // 8 - left
    sGameField * game_field = GAME_FIELD;
    switch(direction)
    {
        case 1:
        case 2:
        case 3:
            index -= game_field->field_size_M;
            break;
        case 5:
        case 6:
        case 7:
            index += game_field->field_size_M;
            break;
    }

    switch(direction)
    {
        case 1:
        case 7:
        case 8:
            index--;
            break;
        case 3:
        case 4:
        case 5:
            index++;
            break;
    }

    if( (game_field->field)[index].power == -1 ) return -1;

    return index;
}

void gmfd_sort(sIstota ** istoty, int istoty_count, bool (*condition)(int, int))
{
   int   i              = 0;
   int   j              = 0;
   sIstota * tmp_istota = NULL;

   for(i = 1; i < istoty_count; i++)
   {
       for(j = 0; j < istoty_count - i; j++)
       {
           if( condition((*(istoty + j))->power, (*(istoty + j + 1))->power) )
           {
               tmp_istota = *(istoty + j);
               *(istoty + j) = *(istoty + j + 1);
               *(istoty + j + 1) = tmp_istota;
           }
       }
   }
}

bool ifMin(int a, int b){ return a > b; }

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

    int  left_margin     = 10;
    int  top_margin      = 1;
    int  cell_width      = 5;

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

        if( str_value != NULL )
        {
            //strlen of str_value must not be more than CW//
            strncpy(str_tmp, str_value, strlen(str_value));
        }

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
