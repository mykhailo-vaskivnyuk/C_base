/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Заняття 8. Типи даних, визначені користувачем (частина 1).
 * Частина 9. Звичайні масиви структур.
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 07.06.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.2.1 Основан на Qt 5.3.2 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/* ЗАВДАННЯ
Реалізуй програму для виконання наступних дій:
1) описати структуру Club з такими полями:
   name - назва клубу;
   sity - місто, яке він представляє;
   place - місце в чемпіонаті (ціле число);
2) оголосити масив структур типу Club (розмірністю не менше 7)
   а також покажчик на двійковий файл;
3) за допомогою циклу заповнити масив структур з клавіатури;
4) вивести отримані структури (дані про клуби) по черзі на екран;
5) відкрити в режимі запису двійковий файл teams.dat;
6) за допомогою циклу - записати структури масиву в даний двійковий файл,
   але в порядку зайнятих місць (починаючи структурою з полем place==1 і далі -
   в порядко зростання значення поля place).
7) після закриття файлу – відкрити його в режимі читання
   і вивести його вміст на екран, переконатися в правильному "сортуванні" клубів.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define STR_MAX_LEN       43
#define STR_CLUB_NAME_LEN 20
#define STR_CLUB_CITY_LEN 20

typedef struct
{
    char club_name[STR_CLUB_NAME_LEN + 1];
    char club_city[STR_CLUB_CITY_LEN + 1];
    int  club_place;
}sClub;

int  inputClubs(sClub **, int *,  FILE *, int);
void addClub   (sClub **, int *,  char *, char *, int);
int  readClubs (sClub **, int,    char *);
void printClubs(sClub *,  int);
void printClub (sClub *,  int);
void sortClubs (sClub *,  int);
void freeClubs (sClub **, int *);
void openFile  (char *,   char *, FILE **);

int main(void)
{
    int           clubs_count_1    = 0;
    sClub       * clubs_1          = NULL;
    FILE        * teams            = NULL;
    char        * file_name        = "teams.dat";
    int           i                = 0;
    size_t        sClub_size       = sizeof(sClub);

//-----------------------------------------------------------------------------
//  input data
//-----------------------------------------------------------------------------

    inputClubs(&clubs_1, &clubs_count_1, NULL, 0);

//-----------------------------------------------------------------------------
//  print data
//-----------------------------------------------------------------------------

    system("cls");
    puts("\0");
    printClubs(clubs_1, clubs_count_1);

//-----------------------------------------------------------------------------
//  sort data
//-----------------------------------------------------------------------------

    sortClubs(clubs_1, clubs_count_1);

//-----------------------------------------------------------------------------
//  write data to file
//-----------------------------------------------------------------------------

    openFile(file_name, "wb", &teams);
    if( !teams ) return 0;
    for(i = 0; i < clubs_count_1; i++)
    {
        fwrite(&clubs_1[i], sClub_size, 1, teams);
    }
    fclose(teams);
    freeClubs(&clubs_1, &clubs_count_1);

//-----------------------------------------------------------------------------
//  read data from file and print
//-----------------------------------------------------------------------------

    puts("\0");
    if( !(clubs_count_1 = readClubs(&clubs_1, 0, file_name)) ) return 0;
    printClubs(clubs_1, clubs_count_1);
    freeClubs(&clubs_1, &clubs_count_1);

//-----------------------------------------------------------------------------

    return 0;
}

//*****************************************************************************
//  OTHER FUNCTIONS
//*****************************************************************************
int inputClubs(sClub ** clubs, int * clubs_count, FILE * input_file, int elements_count)
{
    char   club_name[STR_CLUB_NAME_LEN + 1] = "";
    char   club_city[STR_CLUB_CITY_LEN + 1] = "";
    int    club_place                       = 0;
    sClub  tmp_club                         = {"", "", 0};
    size_t sClub_size                       = sizeof(sClub);

    if( input_file )
    {
        while( fread(&tmp_club, sClub_size, 1, input_file) &&
               (*clubs_count < elements_count || !elements_count) )
            addClub(clubs, clubs_count, tmp_club.club_name, tmp_club.club_city, tmp_club.club_place);

    }
    else
    {
        while( 1 )
        {
            system("cls");
            printClubs(*clubs, *clubs_count);
            printf("ENTER CLUB SITY PLACE: ");

            fflush(stdin);
            club_place = 0;
            scanf("%20s%20s%d", club_name, club_city, &club_place);

            addClub(clubs, clubs_count, club_name, club_city, club_place);

            system("cls");
            printClubs(*clubs, *clubs_count);
            printf("ENTER 'q' TO EXIT OR PRESS ANY KEY TO INPUT NEW RECORD");
            if( 'q' == getch() ) break;
        }
     }

    return 0;
}

void addClub(sClub ** clubs, int * clubs_count, char * club_name, char * club_city, int club_place)
{
    sClub  * club_ptr   = NULL;
    size_t   sClub_size = sizeof(sClub);

    *clubs_count += 1;
    *clubs = (sClub *)realloc(*clubs, sClub_size * (*clubs_count));

    club_ptr = *clubs;
    club_ptr += *clubs_count - 1;

    strcpy(club_ptr->club_name, club_name);
    strcpy(club_ptr->club_city, club_city);
    club_ptr->club_place = club_place;
}

void printClubs(sClub * clubs, int clubs_count)
{
    int i = 0;

    puts("\0");
    puts("     --------------------------------------");
    puts("     | N| place |    club    |    city    |");
    puts("     --------------------------------------");

    for(i = 0; i < clubs_count; i++)
    {
        printClub(&clubs[i], i + 1);
    }
    puts("     --------------------------------------");
    puts("\0");
}

void printClub(sClub * club, int list_number)
{
    printf("     |%2d|%5d  |%-12s|%-12s|\n", list_number,
                                       club->club_place,
                                       club->club_name,
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

int readClubs(sClub ** clubs, int elements_count, char * file_name)
{
    FILE        * teams       = NULL;
    int           clubs_count = 0;

    openFile(file_name, "rb", &teams);
    if( !teams ) return 0;

    inputClubs(clubs, &clubs_count, teams, elements_count);
    fclose(teams);
    return clubs_count;
}

void sortClubs(sClub * clubs,  int clubs_count)
{
   int i = 0;
   int j = 0;
   sClub tmp_club;

   for(i = 0; i < clubs_count - 1; i++)
   {
       for(j = 0; j < clubs_count - 1 - i; j++)
       {
           if(clubs[j].club_place > clubs[j + 1].club_place)
           {
               tmp_club = clubs[j];
               clubs[j] = clubs[j + 1];
               clubs[j + 1] = tmp_club;
           }
       }
   }
}
