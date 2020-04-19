/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Заняття 9. Типи даних, визначені користувачем (частина 2).
 * Частина 2. Об'єднання.
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 10.06.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.2.1 Основан на Qt 5.3.2 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/* ЗАВДАННЯ
Реалізуй програму, виконавши наступні вказівки.
1. Створити такі типи користувача:
   а) перерахування Restype з константами: PLACE i SCORE;
   б) структуру Club з наступними полями:
     name - назва клубу;
     sity - місто, яке представляє клуб;
     info - відповідає типу необхідних даних про результат (константи PLACE i SCORE);
а також полем типу “об’єднання“ Results з внутрішніми полями: place - зайняте місце, score - кількість набраних очок.
2. Вести з клавіатури величину info.
3. За допомогою оператора switch() запрограмувати варіанти введення у поле типу Results результатів клубу (зайняте місце або кількість очок), в залежності від величини info.
4. Ввести дані (назва, місто, зайняте місце або кількість очок) про кілька реальних чи умовних клубів, створивши з них масив структур.
5. Для контролю - пройтися по масиву структур і вивести дані (поля) про кожен клуб.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define STR_MAX_LEN       20
#define STR_CLUB_NAME_LEN 20
#define STR_CLUB_CITY_LEN 20

typedef enum
{
    PLACE
   ,SCORE
}eResType;

typedef union
{
    int place;
    int score;
}uResValue;

typedef struct
{
    char club_name[STR_CLUB_NAME_LEN + 1];
    char club_city[STR_CLUB_CITY_LEN + 1];
    eResType club_res_type;
    uResValue club_res_value;
}sClub;

typedef int (*fptr)(sClub **, int *,  FILE *, int);

void addClub       (sClub **, int *,  char *, char *, eResType, int);
int  inputClubsKey (sClub **, int *,  FILE *, int);
int  inputClubsTxt (sClub **, int *,  FILE *, int);
int  readClubs     (sClub **, char *, int,    fptr);
void printClubs    (sClub *,  int);
void printClub     (sClub *,  int);
void freeClubs     (sClub **, int *);

int  inputNumber   (void);
void openFile      (char *,   char *, FILE **);

int main(void)
{
    int           clubs_count      = 0;
    sClub       * clubs            = NULL;
    char        * input_file_name  = "teams.txt";

//-----------------------------------------------------------------------------
//  input data from keyboard //file
//-----------------------------------------------------------------------------

    //clubs_count = readClubs(&clubs, NULL,            inputNumber(), inputClubsKey);
    clubs_count = readClubs(&clubs, input_file_name, inputNumber(), inputClubsTxt);

//-----------------------------------------------------------------------------
//  print data
//-----------------------------------------------------------------------------

    system("cls");
    puts("\0");
    printClubs(clubs, clubs_count);
    freeClubs(&clubs, &clubs_count);

//-----------------------------------------------------------------------------

    return 0;
}

//*****************************************************************************
//  OTHER FUNCTIONS
//*****************************************************************************
int inputClubsKey(sClub ** clubs, int * clubs_count, FILE * input_file, int elements_count)
{
    char     club_name[STR_CLUB_NAME_LEN + 1] = "";
    char     club_city[STR_CLUB_CITY_LEN + 1] = "";
    eResType club_res_type                    = PLACE;
    int      club_res_value                   = 0;
    char     tmp_str[STR_MAX_LEN]             = "";

    while( elements_count-- || !elements_count )
    {
         system("cls");
         printClubs(*clubs, *clubs_count);

         fflush(input_file);

         printf("ENTER CLUB NAME: ");
         gets(club_name);
         printf("ENTER CLUB CITY: ");
         gets(club_city);
         printf("ENTER CLUB RESULT TYPE (place/score): ");
         gets(tmp_str);
         club_res_type = strstr(tmp_str, "place") ? PLACE : SCORE;
         printf("ENTER CLUB RESULT VALUE: ");
         club_res_value = 0;
         scanf("%d", &club_res_value);

         addClub(clubs, clubs_count, club_name, club_city, club_res_type, club_res_value);

         system("cls");
         printClubs(*clubs, *clubs_count);
         printf("ENTER 'q' TO EXIT OR PRESS ANY KEY TO INPUT NEW RECORD");
         if( 'q' == getch() ) break;
     }

    return 0;
}

int inputClubsTxt(sClub ** clubs, int * clubs_count, FILE * input_file, int elements_count)
{
    char      club_name[STR_CLUB_NAME_LEN + 1] = "";
    char      club_city[STR_CLUB_CITY_LEN + 1] = "";
    eResType  club_res_type                    = PLACE;
    int       club_res_value                   = 0;
    char      tmp_str[STR_MAX_LEN + 1]         = "";
    int       i                                = 1;

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
                //sscanf(tmp_str, "%s", &club_result_type);
                club_res_type = strstr(tmp_str, "place") ?  PLACE : SCORE;
                break;
            case 4:
                sscanf(tmp_str, "%d", &club_res_value);
                break;
        }
        if( i++ == 4 )
        {
            addClub(clubs, clubs_count, club_name, club_city, club_res_type, club_res_value);
            i = 1;
        }
    }

    return 0;
}

void addClub(sClub ** clubs, int * clubs_count, char * club_name, char * club_city, eResType club_res_type, int club_res_value)
{
    sClub  * club_ptr   = NULL;
    size_t   sClub_size = sizeof(sClub);

    *clubs_count += 1;
    *clubs = (sClub *)realloc(*clubs, sClub_size * (*clubs_count));
    if( !*clubs ) exit(0);

    club_ptr = *clubs;
    club_ptr += *clubs_count - 1;

    strcpy(club_ptr->club_name, club_name);
    strcpy(club_ptr->club_city, club_city);
    club_ptr->club_res_type = club_res_type;
    (club_res_type == PLACE) ? (club_ptr->club_res_value.place = club_res_value) :
                               (club_ptr->club_res_value.score = club_res_value);
}

void printClubs(sClub * clubs, int clubs_count)
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

void printClub(sClub * club, int list_number)
{
    if(club->club_res_type == PLACE)
        printf("     |%2d| %5d |       |", list_number,
                                         club->club_res_value.place);
    else
        printf("     |%2d|       | %5d |", list_number,
                                         club->club_res_value.score);
    printf("%-12s|%-12s|\n", club->club_name,
                             club->club_city);
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

void freeClubs(sClub ** clubs, int * clubs_count)
{
    free(clubs);
    *clubs = NULL;
    *clubs_count = 0;
}

int readClubs(sClub ** clubs, char * file_name, int elements_count, fptr input_function)
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
