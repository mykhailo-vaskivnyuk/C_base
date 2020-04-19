/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Заняття 9. Типи даних, визначені користувачем (частина 2).
 * Частина 5. Динамічне виділення пам’яті: функція calloc().
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 12.06.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.2.1 Основан на Qt 5.3.2 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/* ЗАВДАННЯ
Застосуй функцію calloc() для динамічного виділення пам'яті під масив структур:
1) створити структуру Club з наступними полями:
     name - назва клубу;
     city - місто, яке представляє клуб;
     place - зайняте місце в чемпіонаті;
     score - кількість набраних очок.
2) виділити динамічно пам'ять для масиву структур Club розмірністю n (не більше 10 елементів-клубів);
3) в циклі заповнити масив стурктур даними про клуби; в кожній структурі - внести дані лише в окремі поля!
4) вивести дані про клуби на екран (всі поля структур!); переконатися, що незаповнені поля були автоматично обнулені.
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
int  readClubs     (sClub_ptr *, int,    fptr);
void printClubs    (sClub_ptr,   int);
void printClub     (sClub_ptr,   int);
void freeClubs     (sClub_ptr *, int *);

int  inputNumber   (void);

int main(void)
{
    int           clubs_count      = 0;
    sClub_ptr     clubs            = NULL;
    size_t        sClub_size       = sizeof(sClub);

//-----------------------------------------------------------------------------
//  create clubs array
//-----------------------------------------------------------------------------
    clubs_count = inputNumber();
    clubs = (sClub_ptr)calloc(clubs_count, sClub_size);

//-----------------------------------------------------------------------------
//  input data from keyboard
//-----------------------------------------------------------------------------

    clubs_count = readClubs(&clubs, clubs_count, inputClubsKey);

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

void addClub(sClub_ptr * clubs, int * clubs_count, char * club_name, char * club_city, int club_place, int club_score)
{
    sClub_ptr club_ptr   = NULL;

    *clubs_count += 1;

    club_ptr = *clubs;
    club_ptr += *clubs_count - 1;

    strcpy(club_ptr->club_name, club_name);
    //strcpy(club_ptr->club_city, club_city);
    club_ptr->club_place = club_place;
    //club_ptr->club_score = club_score;
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

void freeClubs(sClub_ptr * clubs, int * clubs_count)
{
    free(clubs);
    *clubs = NULL;
    *clubs_count = 0;
}

int readClubs(sClub_ptr * clubs, int elements_count, fptr input_function)
{
    int           clubs_count  = 0;

    input_function(clubs, &clubs_count, stdin, elements_count);

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
