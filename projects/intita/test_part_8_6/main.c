/*----------------------------------------------------------------
 * Алгоритмізація і програмування на мові С.
 * Заняття 8. Типи даних, визначені користувачем (частина 1).
 * Частина 6. Застосування покажчиків в структурах.
 *----------------------------------------------------------------
 * ITA17
 * Vaskivnyuk Mykhailo
 * 05.06.2017
 *----------------------------------------------------------------
 * IDE: Qt Creator 3.2.1 Основан на Qt 5.3.2 (MSVC 2010, 32 бита)
----------------------------------------------------------------*/

/* ЗАВДАННЯ
Реалізуй програму для виконання наступних дій:
1) описати структуру Club з такими полями:
   name - назва клубу;
   sity - місто, яке він представляє;
   place - місце в чемпіонаті (ціле число);
2) оголосити декілька (не менше семи) змінних типу Club;
3) за допомогою циклу - ввести з клавіатури значення полів кожної змінної;
   вибір змінної - через switch(i), де і - лічильник циклу;
4) відкрити в режимі запису текстовий файл teams.txt,
   записати в нього за допомогою циклу всі структури (вибір структури - через switch(i),
   де і - лічильник циклу);
5) після закриття файлу – відкрити його в режимі читання,
   прочитати дані про всі записані клуби і вивести їх на екран (у форматі місце-назва-місто);
6) закрити файл і відкрити його в режимі дозапису в кінець;
7) додати у файл запис (структуру) про ще один клуб: назва – Khaskovo, місто – Khaskovo, місце – 12;
8) заново вивести вміст файлу на екран, переконатися, що всі введені записи про клуби на місці.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define STR_MAX_LEN       43
#define STR_CLUB_NAME_LEN 20
#define STR_CLUB_CITY_LEN 20

struct club
{
    char * club_name;
    char * club_city;
    int    club_place;
};

int  inputClubs(struct club **, int *,  FILE *);
void addClub   (struct club **, int *,  char *, char *, int);
int  readClubs (char *);
void printClubs(struct club *,  int);
void printClub (struct club *,  int);
void freeClubs (struct club **, int *);
void openFile  (char *,         char *, FILE **);

int main(void)
{
    int           clubs_count     = 0;
    struct club * clubs           = NULL;
    FILE        * teams           = NULL;
    char        * file_name       = "teams.txt";
    int           i               = 0;

//-----------------------------------------------------------------------------
//  input data
//-----------------------------------------------------------------------------

    inputClubs(&clubs, &clubs_count, NULL);

//-----------------------------------------------------------------------------
//  write data to file
//-----------------------------------------------------------------------------

    openFile(file_name, "w", &teams);
    if( !teams ) return 0;
    for(i = 0; i < clubs_count; i++)
    {
        fprintf(teams, "%s %s %d\n", clubs[i].club_name,
                                     clubs[i].club_city,
                                     clubs[i].club_place);
    }
    fclose(teams);
    freeClubs(&clubs, &clubs_count);

//-----------------------------------------------------------------------------
//  read data from file and print
//-----------------------------------------------------------------------------

    system("cls");
    if( !readClubs(file_name) ) return 0;

//-----------------------------------------------------------------------------
//  write one more record to file
//-----------------------------------------------------------------------------

    openFile(file_name, "a", &teams);
    if( !teams ) return 0;
    addClub(&clubs, &clubs_count, "Khaskovo", "Khaskovo", 12);
    fprintf(teams, "%s %s %d\n", clubs[clubs_count - 1].club_name,
                                 clubs[clubs_count - 1].club_city,
                                 clubs[clubs_count - 1].club_place);
    fclose(teams);
    freeClubs(&clubs, &clubs_count);

//-----------------------------------------------------------------------------
//  read data from file and print
//-----------------------------------------------------------------------------

    if( !readClubs(file_name) ) return 0;

//-----------------------------------------------------------------------------

    return 0;
}



//*****************************************************************************
//  OTHER FUNCTIONS
//*****************************************************************************
int inputClubs(struct club ** clubs, int * clubs_count, FILE * input_file)
{
    char   tmp_str[STR_MAX_LEN + 1]         = "";
    char   club_name[STR_CLUB_NAME_LEN + 1] = "";
    char   club_city[STR_CLUB_CITY_LEN + 1] = "";
    int    club_place                       = 0;

    if( input_file )
    {
        while( fgets(tmp_str, STR_MAX_LEN + 1, input_file) )
        {
            sscanf(tmp_str, "%20s%20s%d", club_name, club_city, &club_place);
            addClub(clubs, clubs_count, club_name, club_city, club_place);
        }
    }
    else
    {
        while(1)
        {
            system("cls");
            printClubs(*clubs, *clubs_count);
            printf("\nENTER CLUB SITY PLACE: ");

            fflush(stdin);
            club_place = 0;
            scanf("%20s%20s%d", club_name, club_city, &club_place);

            addClub(clubs, clubs_count, club_name, club_city, club_place);

            system("cls");
            printClubs(*clubs, *clubs_count);
            printf("\nENTER 'q' TO EXIT OR PRESS ANY KEY TO INPUT NEW RECORD");
            if( 'q' == getch() ) break;
        }
     }

    return 0;
}

void addClub(struct club ** clubs, int * clubs_count, char * club_name, char * club_city, int club_place)
{
    struct club * club_ptr         = NULL;
    int           struct_club_size = sizeof(struct club);
    size_t        char_size        = sizeof(char);

    *clubs_count += 1;
    *clubs = (struct club *)realloc(*clubs, struct_club_size * (*clubs_count));

    club_ptr = *clubs;
    club_ptr += *clubs_count - 1;

    club_ptr->club_name = (char *)malloc(char_size * (strlen(club_name) + 1));
    strcpy(club_ptr->club_name, club_name);
    club_ptr->club_city = (char *)malloc(char_size * (strlen(club_city) + 1));
    strcpy(club_ptr->club_city, club_city);
    club_ptr->club_place = club_place;

}

void printClubs(struct club * clubs, int clubs_count)
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
}

void printClub(struct club * club, int list_number)
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

void freeClubs(struct club ** clubs, int * clubs_count)
{
    int i = 0;

    for(i = 0; i < *clubs_count; i++)
    {
        free((*clubs)[i].club_name);
        free((*clubs)[i].club_city);
    }
    free(clubs);
    *clubs = NULL;
    *clubs_count = 0;
}

int readClubs(char * file_name)
{
    FILE        * teams       = NULL;
    struct club * clubs       = NULL;
    int           clubs_count = 0;

    openFile(file_name, "r", &teams);
    if( !teams ) return 0;

    inputClubs(&clubs, &clubs_count, teams);
    printClubs(clubs, clubs_count);
    fclose(teams);
    freeClubs(&clubs, &clubs_count);
    return 1;
}
