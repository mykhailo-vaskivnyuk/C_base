/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Заняття 9. Типи даних, визначені користувачем (частина 2).
 * Частина 3. Оператор typedef.
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 11.06.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.2.1 Основан на Qt 5.3.2 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/* ЗАВДАННЯ
Реалізуй програму, використавши оператор typedef наступним чином:
1. Створити структуру Club з наступними полями:
     name - назва клубу;
     city - місто, яке представляє клуб;
     place - зайняте місце в чемпіонаті;
     score - кількість набраних очок.
2. За допомогою оператора typedef створити два синоніми для структури Club -
   для звичайних змінних і для покажчиків;
3. Ввести дані про клуби в масив структур за допомогою синоніма для звичайних змінних;
4. Вивести на екран з масиву структур дані про кожен клуб за допомогою синоніма для покажчиків.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define STR_MAX_LEN       20
#define STR_CLUB_NAME_LEN 20
#define STR_CLUB_CITY_LEN 20

typedef struct
{
    char club_name[STR_CLUB_NAME_LEN + 1];
    char club_city[STR_CLUB_CITY_LEN + 1];
    int  club_place;
    int  club_score;
}sClub, * sClub_ptr;

typedef int (*fptr)(sClub_ptr *, int *,  FILE *, int);

void addClub       (sClub_ptr *, int *,  char *, char *, int, int);
int  inputClubsKey (sClub_ptr *, int *,  FILE *, int);
int  inputClubsTxt (sClub_ptr *, int *,  FILE *, int);
int  readClubs     (sClub_ptr *, char *, int,    fptr);
void printClubs    (sClub_ptr,   int);
void printClub     (sClub_ptr,   int);
void freeClubs     (sClub_ptr *, int *);

int  inputNumber   (void);
void openFile      (char *,      char *, FILE **);

int main(void)
{
    int           clubs_count      = 0;
    sClub_ptr     clubs            = NULL;
    char        * input_file_name  = "teams.txt";

//-----------------------------------------------------------------------------
//  input data from keyboard (txt file)
//-----------------------------------------------------------------------------

    //clubs_count = readClubs(&clubs, NULL, inputNumber(), inputClubsKey);
    clubs_count = readClubs(&clubs, input_file_name, inputNumber(), inputClubsTxt);

//-----------------------------------------------------------------------------
//  print data
//-----------------------------------------------------------------------------

    system("cls");
    puts("\0");
    printClubs(clubs, clubs_count);
    freeClubs(&clubs, & clubs_count);

//-----------------------------------------------------------------------------

    return 0;
}

//*****************************************************************************
//  OTHER FUNCTIONS
//*****************************************************************************
int inputClubsKey(sClub_ptr * clubs, int * clubs_count, FILE * input_file, int elements_count)
{
    char   club_name[STR_CLUB_NAME_LEN + 1] = "";
    char   club_city[STR_CLUB_CITY_LEN + 1] = "";
    int    club_place                       = 0;
    int    club_score                       = 0;

    while( elements_count-- || !elements_count )
    {
         system("cls");
         printClubs(*clubs, *clubs_count);

         fflush(input_file);

         printf("ENTER CLUB NAME: ");
         gets(club_name);
         printf("ENTER CLUB CITY: ");
         gets(club_city);
         printf("ENTER CLUB PLACE: ");
         club_place = 0;
         scanf("%d", &club_place);
         printf("ENTER CLUB SCORE: ");
         fflush(input_file);
         club_score = 0;
         scanf("%d", &club_score);

         addClub(clubs, clubs_count, club_name, club_city, club_place, club_score);

         system("cls");
         printClubs(*clubs, *clubs_count);
         printf("ENTER 'q' TO EXIT OR PRESS ANY KEY TO INPUT NEW RECORD");
         if( 'q' == getch() ) break;
     }

    return 0;
}

int inputClubsTxt(sClub_ptr * clubs, int * clubs_count, FILE * input_file, int elements_count)
{
    char   club_name[STR_CLUB_NAME_LEN + 1] = "";
    char   club_city[STR_CLUB_CITY_LEN + 1] = "";
    int    club_place                       = 0;
    int    club_score                       = 0;
    char   tmp_str[STR_MAX_LEN + 1]         = "";
    int    i                                = 1;

    while( fgets(tmp_str, STR_MAX_LEN + 1, input_file)
           && (*clubs_count < elements_count || !elements_count))
    {
        switch( i )
        {
            case 1:
                sscanf(tmp_str, "%20s", club_name);
                break;
            case 2:
                sscanf(tmp_str, "%20s", club_city);
                break;
            case 3:
                sscanf(tmp_str, "%d", &club_place);
                break;
            case 4:
                sscanf(tmp_str, "%d", &club_score);
                break;
        }
        if( i++ == 4 )
        {
            addClub(clubs, clubs_count, club_name, club_city, club_place, club_score);
            i = 1;
        }
    }

    return 0;
}

void addClub(sClub_ptr * clubs, int * clubs_count, char * club_name, char * club_city, int club_place, int club_score)
{
    sClub_ptr club_ptr   = NULL;
    size_t    sClub_size = sizeof(sClub);

    *clubs_count += 1;
    *clubs = (sClub_ptr)realloc(*clubs, sClub_size * (*clubs_count));
    if( !*clubs ) exit(0);

    club_ptr = *clubs;
    club_ptr += *clubs_count - 1;

    strcpy(club_ptr->club_name, club_name);
    strcpy(club_ptr->club_city, club_city);
    club_ptr->club_place = club_place;
    club_ptr->club_score = club_score;
}

void printClubs(sClub_ptr clubs, int clubs_count)
{
    int i = 0;

    puts("\0");
    puts("     ----------------------------------------------");
    puts("     | N| place | score |    club    |    city    |");
    puts("     ----------------------------------------------");

    for(i = 0; i < clubs_count; i++)
    {
        printClub(&clubs[i], i + 1);
    }
    puts("     ----------------------------------------------");
    puts("\0");
}

void printClub(sClub_ptr club_ptr, int list_number)
{
    printf("     |%2d| %5d | %5d |%-12s|%-12s|\n",
                 list_number,
                 club_ptr->club_place,
                 club_ptr->club_score,
                 club_ptr->club_name,
                 club_ptr->club_city);
}

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
        case 'a':
        case 'w':
            printf("CAN NOT OPEN OR CREATE FILE %s !\n", file_name);
            break;
    }
}

void freeClubs(sClub_ptr * clubs, int * clubs_count)
{
    free(clubs);
    *clubs = NULL;
    *clubs_count = 0;
}

int readClubs(sClub_ptr * clubs, char * file_name, int elements_count, fptr input_function)
{
    FILE        * teams        = NULL;
    int           clubs_count  = 0;

    if( file_name )
    {
        openFile(file_name, "r", &teams);
        if( !teams ) return 0;
    }
    else
        teams = stdin;

    input_function(clubs, &clubs_count, teams, elements_count);
    fclose(teams);
    return clubs_count;
}

int  inputNumber(void)
{
    int clubs_count = 0;
    while(1)
    {
        if( clubs_count < 0 )
        {
            puts("\nWRONG NUMBER! TRY AGAIN!");
        }
        printf("\nINPUT CLUBS COUNT/NUMBER TO READ: ");
        fflush(stdin);
        clubs_count = 0;
        scanf("%d", &clubs_count);
        if( clubs_count > 0 ) break;
        clubs_count = -1;
    }

    return clubs_count;
}
